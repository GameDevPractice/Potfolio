#include "CEnemy.h"
#include "Global.h"
#include "Character/Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Component/CMontageComponent.h"
#include "Component/CAttributeComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "AIController.h"
#include "Blueprint/UserWidget.h"
#include "UI/CWorldWidget.h"
#include "Action/CAction.h"
#include "Action/CAttachment.h"

ACEnemy::ACEnemy()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	CHelpers::CreateSceneComponent(this, &BoxComp, TEXT("BoxComp"), GetMesh());
	BoxComp->SetRelativeLocation(FVector(-0.000008f, -59.999950f, 100.000000f));
	BoxComp->SetBoxExtent(FVector(32.f,32.f,88.f));

	//ActionComponet
	CHelpers::CreateActorComponent(this, &ActionComp, TEXT("ActionComp"));
	//MontageComponet
	CHelpers::CreateActorComponent(this, &MontageComp, TEXT("MontageComp"));
	//StateComponent
	CHelpers::CreateActorComponent(this, &StateComp, TEXT("StateComp"));
	//AttributeComponet
	CHelpers::CreateActorComponent(this, &AttributeComp, TEXT("Attribute"));

	
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	StateComp->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnTakeDown);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACEnemy::OffTakeDown);

	AIC = GetController<AAIController>();

	if (TakeOverClass)
	{

		TakeOverWidget = CreateWidget<UCWorldWidget>(GetWorld(), TakeOverClass);
		if (TakeOverWidget)
		{
			TakeOverWidget->AttachToActor = this;
			TakeOverWidget->AddToViewport();
			TakeOverWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	//Check DataTable
	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not Set");
		return;
	}

	//Save Montage
	TArray<FEnemyStealthTakeDown*> FromDatasTable;
	DataTable->GetAllRows<FEnemyStealthTakeDown>("", FromDatasTable);

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		for (const auto& Data : FromDatasTable)
		{
			if ((EActionType)i == Data->Type)
			{
				StealthTakeDownData[i] = Data;
				break;
			}
		}
	}

}

void ACEnemy::StealTakeDown(bool InCrouch, EActionType InActionType)
{
	
	switch (InActionType)
	{
	case EActionType::UnArmed:
	{
		OnStandingUnArmed(InCrouch, InActionType);
		break;
	}
	case EActionType::Sword:
	{
		InCrouch ? OnStandingSword(InCrouch,InActionType) : OnCrounhSword(InCrouch,InActionType);
		break;
	}
	case EActionType::Pistol:
	{
		break;
	}
	default:
		break;
	}
}


void ACEnemy::OnTakeDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}
	Player->OnTakeDown();
	TakeOverWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACEnemy::OffTakeDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}
	Player->OffTakeDown();
	TakeOverWidget->SetVisibility(ESlateVisibility::Hidden);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageInstigator = EventInstigator;



	//ActionComp->Abort();
	AttributeComp->OnDecreseHealth(Damage);

	if (AttributeComp->GetCurrentHealth() <= 0)
	{
	
		StateComp->SetDeadMode();
		return 0.0f;
	}

	StateComp->SetHittedMode();

	return DamageValue;
}

void ACEnemy::EnemyDestroy()
{
	ActionComp->GetCurrentAction()->GetAttachment()->Destroy();
	Destroy();
}

void ACEnemy::Hitted()
{
	MontageComp->PlayHitted();
}

void ACEnemy::Dead()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	FTimerHandle DeadHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this,TEXT("EnemyDestroy"));
	GetWorldTimerManager().SetTimer(DeadHandle, Delegate,2.0f,false);
}

void ACEnemy::TagetWidgetOn()
{
	CheckNull(TakeOverWidget);
	TakeOverWidget->SetVisibility(ESlateVisibility::Visible) ;
	
}

void ACEnemy::OnStandingSword(bool InCrouch,EActionType InType)
{
	FEnemyStealthTakeDown* Data = StealthTakeDownData[(int32)InType];
	CheckNull(Data->Montage[(int32)InCrouch]);
	float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch], Data->PlayRate, Data->StartSection);

	FTimerDelegate TakeDownDelegate;
	TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
	GetCharacterMovement()->DisableMovement();

	GetWorldTimerManager().SetTimer(TakeDownHandle, TakeDownDelegate, MontageTime - 0.2f, false);
}

void ACEnemy::OnCrounhSword(bool InCrouch,EActionType InType)
{
	FEnemyStealthTakeDown* Data = StealthTakeDownData[(int32)InType];
	CheckNull(Data->Montage[(int32)InCrouch]);
	float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch], Data->PlayRate, Data->StartSection);

	FTimerDelegate TakeDownDelegate;
	TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
	GetCharacterMovement()->DisableMovement();

	GetWorldTimerManager().SetTimer(TakeDownHandle, TakeDownDelegate, MontageTime - 0.2f, false);
}

void ACEnemy::OnStandingUnArmed(bool InCrouch, EActionType InType)
{
	FEnemyStealthTakeDown* Data = StealthTakeDownData[(int32)InType];
	CheckNull(Data->Montage[(int32)InCrouch]);
	float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch], Data->PlayRate, Data->StartSection);

	FTimerDelegate TakeDownDelegate;
	TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
	GetCharacterMovement()->DisableMovement();

	GetWorldTimerManager().SetTimer(TakeDownHandle, TakeDownDelegate, MontageTime - 0.2f, false);
}

void ACEnemy::TakeDown(bool InCrouch, EActionType InType)
{
	StealTakeDown(InCrouch, InType);
}

void ACEnemy::EndTakeDown()
{
	GetWorldTimerManager().ClearTimer(TakeDownHandle);
	GetMesh()->SetSimulatePhysics(true);
	AIC->UnPossess();
	ActionComp->GetCurrentAction()->GetAttachment()->Destroy();
	Destroy();
}

void ACEnemy::TagetWidgetOff()
{
	CheckNull(TakeOverWidget);
	TakeOverWidget->SetVisibility(ESlateVisibility::Hidden);

}


void ACEnemy::OnStateTypeChanged(EStateType PreType, EStateType NewType)
{
	switch (NewType)
	{
	
	case EStateType::Hitted:
	{
		Hitted();
		break;
	}
	case EStateType::Dead:
	{
		Dead();
		break;
	}
	default:
		break;
	}
}


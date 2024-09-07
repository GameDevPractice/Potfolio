#include "CEnemy.h"
#include "Global.h"
#include "Character/Player/CPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Component/CActionComponent.h"
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
	USkeletalMesh* MeshComp;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Enemy/Mesh/Swat"));
	if (MeshAsset.Succeeded())
	{
		MeshComp = MeshAsset.Object;
		GetMesh()->SetSkeletalMesh(MeshComp);
	}

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

	if (TargetWidgetClass)
	{

		TargetWidget = CreateWidget<UCWorldWidget>(GetWorld(), TargetWidgetClass);
		if (TargetWidget)
		{
			TargetWidget->AttachToActor = this;
			TargetWidget->AddToViewport();
			TargetWidget->SetVisibility(ESlateVisibility::Hidden);
		}
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
}

void ACEnemy::OffTakeDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}
	Player->OffTakeDown();
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

void ACEnemy::Hitted()
{
	MontageComp->PlayHitted();
}

void ACEnemy::Dead()
{
	MontageComp->PlayDead();
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIC->UnPossess();
}

void ACEnemy::TagetWidgetOn()
{
	CheckNull(TargetWidget);
	TargetWidget->SetVisibility(ESlateVisibility::Visible) ;
	
}

void ACEnemy::TakeDown()
{
	if (TakeDownMontage == nullptr)
	{
		return;
	}
	float MontageTime = PlayAnimMontage(TakeDownMontage);

	FTimerDelegate TakeDownDelegate;
	TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));

	GetWorldTimerManager().SetTimer(TakeDownHandle, TakeDownDelegate, MontageTime-0.2f, false);
	
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
	CheckNull(TargetWidget);
	TargetWidget->SetVisibility(ESlateVisibility::Hidden);

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


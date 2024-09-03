#include "Action/CDoAction_Katana.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CAttributeComponent.h"


void ACDoAction_Katana::DoAction()
{
	Super::DoAction();
	CheckFalse(Data.Num() > 0);
	if (bcanCombo)
	{
		bcanCombo = false;
		bSuccessCombo = true;

		return;
	}
	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Data[0].AnimMontage, Data[0].PlayRate, Data[0].StartSection);
	Data[0].SetMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Katana::EnableCombo()
{
	bcanCombo = true;
}

void ACDoAction_Katana::DisableCombo()
{
	bcanCombo = false;
}



void ACDoAction_Katana::Begin_DoAction()
{
	Super::Begin_DoAction();
	
	CheckFalse(bSuccessCombo);
	bSuccessCombo = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Data.Num() - 1);
	CLog::Print(ComboCount);

	OwnerCharacter->PlayAnimMontage(Data[ComboCount].AnimMontage, Data[ComboCount].PlayRate, Data[ComboCount].StartSection);
	Data[0].SetMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
	
}

void ACDoAction_Katana::End_DoAction()
{
	Super::End_DoAction();
	
	OwnerCharacter->StopAnimMontage();
	ComboCount = 0;

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_Katana::OnAttachBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	FDamageEvent DamageEvent;
	InOtherCharacter->TakeDamage(Data[ComboCount].Power, DamageEvent,InAttacker->GetController(),InCauser);

	//CameraShake
	TSubclassOf<UCameraShake> ShakeClass = Data[ComboCount].CameraShake;
	if (ShakeClass)
	{
		
		if (PC)
		{
			PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
		}
	}

	//Hit Effect
	UParticleSystem* HitEffect = Data[ComboCount].Particle;
	if (HitEffect)
	{
		FTransform Transform = Data[ComboCount].EffectTransforms;
		Transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Transform);
	}
}

void ACDoAction_Katana::OnAttachEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

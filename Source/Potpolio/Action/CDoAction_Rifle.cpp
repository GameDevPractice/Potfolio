#include "Action/CDoAction_Rifle.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Component/CMontageComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CBehaviorComponent.h"
#include "Action/CAction.h"
#include "Action/CAttachment.h"
#include "Action/CBullet.h"
#include "Camera/CameraShake.h"
#include "DrawDebugHelpers.h"
#include "AI/CAIController.h"

ACDoAction_Rifle::ACDoAction_Rifle()
{
}

void ACDoAction_Rifle::BeginPlay()
{
	Super::BeginPlay();
	MontageComp = CHelpers::GetComponent<UCMontageComponent>(OwnerCharacter);

	MaxBulletCount = Data[0].MaxBullet;
	CurrentBulletCount = MaxBulletCount;
}

void ACDoAction_Rifle::DoAction()
{
	if (CurrentBulletCount <= 0)
	{
		CLog::Print("Not Bullet");
		UCBehaviorComponent* BehaviorComp = AIC->GetBehaviorComp();
		CheckNull(BehaviorComp);
		BehaviorComp->SetReloadMode();
	}
	else
	{

	OwnerCharacter->PlayAnimMontage(Data[0].AnimMontage, Data[0].PlayRate);
	CheckNull(Data[0].Bullet);

	CurrentBulletCount--;

	CheckNull(ActionComp);

	ActionData = ActionComp->GetCurrentAction();
	CheckNull(ActionData);
	Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);

	//Spawn Bullet
	FTransform Transform;

	FVector MuzzleLocation = Attachment->GetMesh()->GetSocketLocation("MuzzleFlash");
	FVector CamLoc;
	FRotator CamRot;

	AIC->GetPlayerViewPoint(CamLoc, CamRot);

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	QueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionShape Shape;
	Shape.SetSphere(20.f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = OwnerCharacter->GetInstigator();

	FHitResult TraceHit;
	FVector TraceStart = CamLoc;
	FVector TraceEnd = TraceStart + (CamRot.Vector() * 100000.f);

	FRotator Rotation = FRotationMatrix::MakeFromX(TraceEnd - MuzzleLocation).Rotator();
	FTransform SpawnTransform(Rotation, MuzzleLocation);
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red,false,5.f);


	Bullet = GetWorld()->SpawnActor<ACbullet>(Data[0].Bullet, SpawnTransform, SpawnParam);

	//Bind BulletDelegate
	Bullet->OnBulletBeginOverlap.AddDynamic(this, &ACDoAction_Rifle::OnBulletBeginOverlap);

	USoundBase* RiflelSound = Attachment->GetSound();

	UGameplayStatics::PlaySound2D(GetWorld(), RiflelSound);

	}
}

void ACDoAction_Rifle::OnBulletBeginOverlap(FHitResult InHitResult)
{
	FHitResult HitResult = InHitResult;

	if (Data[0].Particle)
	{
		FTransform EffectLocation = Data[0].EffectTransforms;
		EffectLocation.AddToTranslation(Bullet->GetActorLocation());
		EffectLocation.SetRotation(FQuat(HitResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Data[0].Particle, EffectLocation);
	}

	FDamageEvent DamageEvent;
	HitResult.GetActor()->TakeDamage(Data[0].Power, DamageEvent, PC, this);
}

void ACDoAction_Rifle::OnReload()
{

	CurrentBulletCount = MaxBulletCount;
}


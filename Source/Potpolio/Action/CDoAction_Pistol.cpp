#include "CDoAction_Pistol.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CAttachment.h"
#include "Action/CBullet.h"
#include "Aim.h"
#include "Camera/CameraShake.h"



ACDoAction_Pistol::ACDoAction_Pistol()
{
	Aim = CreateDefaultSubobject<UAim>("Aim");
}

void ACDoAction_Pistol::BeginPlay()
{
	Super::BeginPlay();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Pistol::DoAction()
{
	CheckNull(Data[0].Bullet);
	CheckFalse(bAiming);

	//Spawn Bullet
	FTransform Transform;
	ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);
	FVector MuzzleLocation = Attachment->GetMesh()->GetSocketLocation("MuzzleFlash");
	UParticleSystem* Particle = Attachment->GetParticle();
	UGameplayStatics::SpawnEmitterAttached(Particle, Attachment->GetMesh(), "MuzzleFlash");

	FVector CamLoc;
	FRotator CamRot;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CamLoc, CamRot);


	Transform.SetLocation(MuzzleLocation);
	Transform.SetRotation(FQuat(CamRot));

	Bullet = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACbullet>(Data[0].Bullet, Transform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//Finish Spawn
	Bullet->FinishSpawning(Transform);

	//Bind BulletDelegate
	Bullet->OnBulletBeginOverlap.AddDynamic(this, &ACDoAction_Pistol::OnBulletBeginOverlap);

	//Play Sound
	USoundBase* PistolSound = Attachment->GetSound();
	
	UGameplayStatics::PlaySound2D(GetWorld(), PistolSound);


	//Play CameraShake
	CheckNull(Data[0].CameraShake);
	PC->PlayerCameraManager->PlayCameraShake(Data[0].CameraShake);
}

void ACDoAction_Pistol::SubDoAction(bool InbAiming)
{
	bAiming = InbAiming;
	Aim->SetVisiblity(InbAiming);
}

void ACDoAction_Pistol::OnBulletBeginOverlap(FHitResult InHitResult)
{
	FHitResult HitResult = InHitResult;
	if (Data[0].Particle)
	{
		FTransform EffectLocation = Data[0].EffectTransforms;
		EffectLocation.AddToTranslation(HitResult.ImpactPoint);
		EffectLocation.SetRotation(FQuat(HitResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Data[0].Particle, EffectLocation);
	}

	FDamageEvent DamageEvent;
	HitResult.GetActor()->TakeDamage(Data[0].Power,DamageEvent,PC,this);

	CLog::Print(Data[0].Power);
}



#include "CDoAction_Pistol.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CAttachment.h"
#include "Action/CBullet.h"
#include "Aim.h"



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

	FTransform Transform;
	ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);
	FVector MuzzleLocation = Attachment->GetMesh()->GetSocketLocation("MuzzleFlash");

	FVector CamLoc;
	FRotator CamRot;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CamLoc, CamRot);

	FVector SpanwLocation = CamLoc + CamRot.Vector() * ((MuzzleLocation - CamLoc) | CamRot.Vector());

	Transform.SetLocation(SpanwLocation);
	Transform.SetRotation(FQuat(CamRot));

	UGameplayStatics::SpawnEmitterAttached(Data[0].Particle, Attachment->GetMesh(), "MuzzleFlash");
	Bullet = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACbullet>(Data[0].Bullet, Transform,OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Bullet->FinishSpawning(Transform);

	CamLoc = FVector::ZeroVector;
	CamRot = FRotator::ZeroRotator;
}

void ACDoAction_Pistol::SubDoAction(bool InbAiming)
{
	bAiming = InbAiming;
	Aim->SetVisiblity(InbAiming);
}



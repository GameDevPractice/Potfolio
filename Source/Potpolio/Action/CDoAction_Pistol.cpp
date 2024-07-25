#include "CDoAction_Pistol.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CAttachment.h"
#include "Action/CBullet.h"



ACDoAction_Pistol::ACDoAction_Pistol()
{
	
}

void ACDoAction_Pistol::BeginPlay()
{
	Super::BeginPlay();
}

void ACDoAction_Pistol::DoAction()
{
	FTransform Transform;
	ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);
	FVector MuzzleLocation = Attachment->GetMesh()->GetSocketLocation("MuzzleFlash");
	Transform.SetLocation(MuzzleLocation);
	CLog::Print(Transform.GetLocation());
	UGameplayStatics::SpawnEmitterAttached(Data[0].Particle, Attachment->GetMesh(), "MuzzleFlash");
	Bullet = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACbullet>(Data[0].Bullet, Transform,OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Bullet->FinishSpawning(Transform);
}

void ACDoAction_Pistol::SubDoAction(bool InbAiming)
{
	bAiming = InbAiming;
}



#include "Animation/CAnimNotify_OffPlayerCollision.h"
#include "Global.h"
#include "Character/Player/CPlayer.h"

FString UCAnimNotify_OffPlayerCollision::GetNotifyName_Implementation() const
{
	return "OffPlayerCollision";
}

void UCAnimNotify_OffPlayerCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());
	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());

	CheckNull(Player);
	Player->OffCollision();


}

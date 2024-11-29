#include "Animation/CAnimNotify_PlayerCollision.h"
#include "Global.h"
#include "Character/Player/CPlayer.h"

FString UCAnimNotify_PlayerCollision::GetNotifyName_Implementation() const
{
	return "PlayerCollision";
}

void UCAnimNotify_PlayerCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());
	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);
	Player->OnCollision();
	

}

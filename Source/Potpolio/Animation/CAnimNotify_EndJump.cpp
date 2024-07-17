#include "CAnimNotify_EndJump.h"
#include "Global.h"
#include "Character/Player/CPlayer.h"

FString UCAnimNotify_EndJump::GetNotifyName_Implementation() const
{
	return "EndJump";
}

void UCAnimNotify_EndJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACPlayer* OwnerCharacter = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(OwnerCharacter);
	OwnerCharacter->End_Jump();
}

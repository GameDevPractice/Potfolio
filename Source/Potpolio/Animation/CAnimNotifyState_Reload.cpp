#include "Animation/CAnimNotifyState_Reload.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CAction.h"
#include "ACtion/CDoAction_Pistol.h"
#include "Character/Player/CPlayer.h"

FString UCAnimNotifyState_Reload::GetNotifyName() const
{
    return "Reload";
}

void UCAnimNotifyState_Reload::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCAction* ActionData = ActionComp->GetCurrentAction();
    CheckNull(ActionData);

    ACDoAction_Pistol* DoAction = Cast<ACDoAction_Pistol>(ActionData->GetDoAction());
    CheckNull(DoAction);

    DoAction->OnReload();

}

void UCAnimNotifyState_Reload::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(Player);

    Player->End_Reload();
}

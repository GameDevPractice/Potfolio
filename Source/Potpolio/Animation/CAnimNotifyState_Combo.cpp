#include "Animation/CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CAction.h"
#include "Action/CDoAction_Katana.h"


FString UCAnimNotifyState_Combo::GetNotifyName() const
{
    return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);
    UCAction* Action = ActionComp->GetCurrentAction();
    CheckNull(Action);
    ACDoAction_Katana* DoAction = Cast<ACDoAction_Katana>(Action->GetDoAction());
    CheckNull(DoAction);
    DoAction->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);
    UCAction* Action = ActionComp->GetCurrentAction();
    CheckNull(Action);
    ACDoAction_Katana* DoAction = Cast<ACDoAction_Katana>(Action->GetDoAction());
    CheckNull(DoAction);
    DoAction->DisableCombo();
}

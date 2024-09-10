#include "Animation/CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CAction.h"
#include "Action/CAttachment.h"
#include "Action/CDoAction_Katana.h"


FString UCAnimNotifyState_Collision::GetNotifyName() const
{
    return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);
    UCAction* Action = ActionComp->GetCurrentAction();
    CheckNull(Action);
    ACAttachment* Attachment = Action->GetAttachment();
    CheckNull(Attachment);
    Attachment->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);
    UCAction* Action = ActionComp->GetCurrentAction();
    CheckNull(Action);
    ACAttachment* Attachment = Action->GetAttachment();
    CheckNull(Attachment);
    Attachment->OffCollisions();
    ACDoAction_Katana* DoAction = Cast<ACDoAction_Katana>(Action->GetDoAction());
    CheckNull(DoAction);
    DoAction->ClearHittedCharacter();

}

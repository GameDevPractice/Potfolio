#include "CAnimNotify_EndAction.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CAction.h"
#include "Action/CAction.h"
#include "Action/CDoAction.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "End_Action";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentAction();
	CheckNull(ActionData);

	ACDoAction* DoAction = ActionData->GetDoAction();
	CheckNull(DoAction);

	DoAction->End_DoAction();
}

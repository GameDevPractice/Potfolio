#include "CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CAction.h"
#include "Action/CDoAction.h"


FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_Action";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentAction();
	CheckNull(ActionData);

	ACDoAction* DoAction = ActionData->GetDoAction();
	CheckNull(DoAction);

	DoAction->Begin_DoAction();

}

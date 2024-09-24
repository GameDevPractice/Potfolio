#include "CAnimNotify_ComboUp.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CAction.h"
#include "Action/CDoAction.h"
#include "Action/CDoAction_Katana.h"


FString UCAnimNotify_ComboUp::GetNotifyName_Implementation() const
{
	return "ComboUp";
}

void UCAnimNotify_ComboUp::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentAction();
	CheckNull(ActionData);

	ACDoAction* DoAction = ActionData->GetDoAction();
	CheckNull(DoAction);

	ACDoAction_Katana* DoAction_Katana = Cast<ACDoAction_Katana>(DoAction);
	CheckNull(DoAction_Katana);

	DoAction_Katana->IncreasCount();

}

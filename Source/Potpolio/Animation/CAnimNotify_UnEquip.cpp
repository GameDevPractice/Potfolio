#include "CAnimNotify_UnEquip.h"
#include "Global.h"
#include "Component/CStateComponent.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


FString UCAnimNotify_UnEquip::GetNotifyName() const
{
	return FString("EndUnEquip");
}

void UCAnimNotify_UnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
    CheckNull(StateComp);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	UCAttributeComponent* AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	if (ActionComp->IsCanUnArm())
	{
		ActionComp->SetUnarmedMode();
	}
	if (ActionComp->IsCanChange())
	{
		ActionComp->ChangeEquip(ActionComp->GetCurrentType());
	}

    StateComp->SetIdleMode();
	AttributeComp->SetMove();

}

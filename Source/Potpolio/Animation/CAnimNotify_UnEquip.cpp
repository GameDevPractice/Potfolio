#include "CAnimNotify_UnEquip.h"
#include "Global.h"
#include "Component/CStateComponent.h"


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

    StateComp->SetIdleMode();

}

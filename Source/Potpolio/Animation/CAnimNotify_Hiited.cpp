#include "Animation/CAnimNotify_Hiited.h"
#include "Global.h"
#include "Component/CStateComponent.h"


FString UCAnimNotify_Hiited::GetNotifyName() const
{
	return FString("Hitted");
}

void UCAnimNotify_Hiited::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(StateComp);
	StateComp->SetIdleMode();

}

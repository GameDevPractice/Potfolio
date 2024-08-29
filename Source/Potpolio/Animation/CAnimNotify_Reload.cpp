#include "Animation/CAnimNotify_Reload.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CAction.h"
#include "Action/CDoAction_Rifle.h"


FString UCAnimNotify_Reload::GetNotifyName() const
{
	return FString("Reload");
}

void UCAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);
	UCAction* Action = ActionComp->GetCurrentAction();
	CheckNull(Action);
	ACDoAction_Rifle* DoACtion_Rifle = Cast<ACDoAction_Rifle>(Action->GetDoAction());
	CheckNull(DoACtion_Rifle);
	DoACtion_Rifle->OnReload();

}

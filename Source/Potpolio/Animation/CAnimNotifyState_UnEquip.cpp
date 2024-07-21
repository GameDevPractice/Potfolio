#include "CAnimNotifyState_UnEquip.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Action/CActionData.h"
#include "Action/CEquipment.h"

FString UCAnimNotifyState_UnEquip::GetNotifyName() const
{
	return FString("UnEquip");
}

void UCAnimNotifyState_UnEquip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionData* ActionData = ActionComp->GetCurrentActionData();
    CheckNull(ActionData);

    ACEquipment* Equipment = ActionData->GetEquipment();
    CheckNull(Equipment);

    
    Equipment->Begin_UnEquip();
}

void UCAnimNotifyState_UnEquip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionData* ActionData = ActionComp->GetCurrentActionData();
    CheckNull(ActionData);

    ACEquipment* Equipment = ActionData->GetEquipment();
    CheckNull(Equipment);

  
    Equipment->End_UnEquip();
}


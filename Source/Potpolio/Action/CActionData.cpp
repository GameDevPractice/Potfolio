#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform Transform;
	
	//Attachment Attach
	if (AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, Transform, InOwnerCharacter);
		Attachment->FinishSpawning(Transform);
	}


	//Equipment Attach
	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, Transform,InOwnerCharacter);
		Equipment->SetData(EquipData);
		Equipment->FinishSpawning(Transform);
		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}
}


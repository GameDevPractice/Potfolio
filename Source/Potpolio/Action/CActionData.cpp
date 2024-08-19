#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "CAction.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCAction** OutAction)
{
	FTransform Transform;

	ACAttachment* Attachment = nullptr;
	
	//Attachment Attach
	if (AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, Transform, InOwnerCharacter);
		Attachment->FinishSpawning(Transform);
	}

	ACEquipment* Equipment = nullptr;
	//Equipment Attach
	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, Transform,InOwnerCharacter);
		Equipment->SetData(EquipData);
		Equipment->SetUnData(UnEquipData);
		Equipment->FinishSpawning(Transform);
		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}

	ACDoAction* DoAction = nullptr;
	//DoAction
	if (DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass,Transform,InOwnerCharacter);
		DoAction->SetActionData(DoActionData);
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), NAME_None);
		DoAction->FinishSpawning(Transform);
	}

	*OutAction = NewObject<UCAction>();
	(*OutAction)->Attachment = Attachment;
	(*OutAction)->Equipment = Equipment;
	(*OutAction)->DoAction = DoAction;

}


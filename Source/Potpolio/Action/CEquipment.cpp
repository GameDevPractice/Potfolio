#include "CEquipment.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CAttributeComponent.h"
#include "Component/CActionComponent.h"

ACEquipment::ACEquipment()
{
}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(OwnerCharacter);
	ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
}

void ACEquipment::SetData(const FEquipData& InData)
{
	Data = InData;
}

void ACEquipment::SetUnData(const FUnEquipData& InData)
{
	UnData = InData;
}



void ACEquipment::Equip_Implementation()
{
	StateComp->SetEquipMode();

	if (Data.AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
	{
		OnEquipmentDelegate.Broadcast();
	}
}

void ACEquipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();
}

void ACEquipment::UnEquip_Implementation()
{
	
	if (UnData.AnimMontage)
	{
	 OwnerCharacter->PlayAnimMontage(UnData.AnimMontage, UnData.PlayRate, UnData.StartSection);
	}
	else
	{
		Begin_UnEquip();
		End_UnEquip();
	}
	
}

void ACEquipment::Begin_UnEquip_Implementation()
{
	StateComp->SetUnEquipMode();
}

void ACEquipment::End_UnEquip_Implementation()
{
	if (OnUnequipmentDelegate.IsBound())
	{
		OnUnequipmentDelegate.Broadcast();
	}
}
#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Action/CActionData.h"
#include "Action/CEquipment.h"

UCActionComponent::UCActionComponent()
{
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	//데이터애셋을 여기서 스폰
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (DataAssets[i])
		{
			DataAssets[i]->BeginPlay(OwnerCharacter);
		}

	}
	
}

void UCActionComponent::SetUnarmedMode()
{
	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetEquipment())
	{
		DataAssets[(int32)Type]->GetEquipment()->UnEquip();
	}

	DataAssets[(int32)EActionType::UnArmed]->GetEquipment()->Equip();

	ChangeMode(EActionType::UnArmed);
}

void UCActionComponent::SetSwordMode()
{
	SetMode(EActionType::Sword);
}


void UCActionComponent::SetPistolMode()
{
	SetMode(EActionType::Pistol);
}

void UCActionComponent::SetMode(EActionType InNextType)
{
	if (Type == InNextType)
	{
		ChangeMode(EActionType::UnArmed);
		return;
	}
	ChangeMode(InNextType);
}

void UCActionComponent::ChangeMode(EActionType InNextType)
{
	if (Type == InNextType)
	{
		SetUnarmedMode();
		return;
	}

	else if (IsUnarmedMode() == false)
	{
		if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetEquipment())
		{
			DataAssets[(int32)Type]->GetEquipment()->UnEquip();
		}
	}
	if (DataAssets[(int32)InNextType] && DataAssets[(int32)InNextType]->GetEquipment())
	{
		DataAssets[(int32)InNextType]->GetEquipment()->Equip();
	}

}

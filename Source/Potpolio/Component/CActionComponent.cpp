#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Action/CActionData.h"
#include "Action/CEquipment.h"
#include "Action/CDoAction.h"

UCActionComponent::UCActionComponent()
{
	CanUnArm = false;
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

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = DataAssets[(int32)Type]->GetDoAction();
		DoAction->DoAction();
	}
}

void UCActionComponent::DoSubAction(bool InbAiming)
{
	CheckFalse(IsPistolMode());

	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = DataAssets[(int32)Type]->GetDoAction();
		DoAction->SubDoAction(InbAiming);
		if (ONAimChanged.IsBound())
		{
			ONAimChanged.Broadcast(InbAiming);
		}
	}
}

void UCActionComponent::SetUnarmedMode()
{
	DataAssets[(int32)EActionType::UnArmed]->GetEquipment()->Equip();
	CanUnArm = false;
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
		CanUnArm = true;
		if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetEquipment())
		{
			DataAssets[(int32)Type]->GetEquipment()->UnEquip();
		}
		return;
	}
	else
	{
		CanUnArm = false;
	}

	if (DataAssets[(int32)InNextType] && DataAssets[(int32)InNextType]->GetEquipment())
	{
		
		DataAssets[(int32)InNextType]->GetEquipment()->Equip();
		ChangeMode(InNextType);
	}
}

void UCActionComponent::ChangeMode(EActionType InNextType)
{
	
	EActionType Prev = Type;
	Type = InNextType;

	if (OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.Broadcast(Prev, InNextType);
	}

}

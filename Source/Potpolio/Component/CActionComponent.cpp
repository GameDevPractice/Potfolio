#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Action/CActionData.h"
#include "Action/CEquipment.h"
#include "Action/CDoAction.h"
#include "Action/CAction.h"

UCActionComponent::UCActionComponent()
{
	CanUnArm = false;
	CanChange = false;
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
			DataAssets[i]->BeginPlay(OwnerCharacter,&Datas[i]);
		}

	}
	Type = EActionType::UnArmed;
	
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (Datas[(int32)Type] && Datas[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = Datas[(int32)Type]->GetDoAction();
		DoAction->DoAction();
	}
}

void UCActionComponent::DoSubAction(bool InbAiming)
{
	CheckFalse(IsPistolMode());

	if (Datas[(int32)Type] && Datas[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = Datas[(int32)Type]->GetDoAction();
		DoAction->SubDoAction(InbAiming);
		if (ONAimChanged.IsBound())
		{
			ONAimChanged.Broadcast(InbAiming);
		}
	}
}



void UCActionComponent::SetUnarmedMode()
{
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

void UCActionComponent::SetRifleMode()
{
	SetMode(EActionType::Rifle);
}

void UCActionComponent::SetMode(EActionType InNextType)
{
	if (Type == EActionType::UnArmed)
	{
		ChangeEquip(InNextType);
		return;
	}
	
	if (Type == InNextType)
	{
		CanUnArm = true;
		CanChange = false;
	}
	else
	{	
		CanUnArm = false;
		CanChange = true;
	}
	if (Datas[(int32)Type] && Datas[(int32)Type]->GetEquipment())
	{
		Datas[(int32)Type]->GetEquipment()->UnEquip();
	}
	NextType = InNextType;
}

void UCActionComponent::ChangeEquip(EActionType InNextType)
{
	CanChange = false;
	if (Datas[(int32)InNextType] && Datas[(int32)InNextType]->GetEquipment())
	{
		Datas[(int32)InNextType]->GetEquipment()->Equip();
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

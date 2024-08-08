#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCStateComponent::SetIdleMode()
{
	ChangeMode(EStateType::Idle);
}

void UCStateComponent::SetJumpMode()
{
	ChangeMode(EStateType::Jump);
}

void UCStateComponent::SetEquipMode()
{
	ChangeMode(EStateType::Equip);
}

void UCStateComponent::SetUnEquipMode()
{
	ChangeMode(EStateType::UnEquip);
}

void UCStateComponent::SetActionMode()
{
	ChangeMode(EStateType::Action);
}

void UCStateComponent::SetHittedMode()
{
	ChangeMode(EStateType::Hitted);
}

void UCStateComponent::SetDeadMode()
{
	ChangeMode(EStateType::Dead);
}

void UCStateComponent::SetReloadMode()
{
	ChangeMode(EStateType::Reload);
}

void UCStateComponent::ChangeMode(EStateType InNewType)
{
	
	if (OnStateTypeChanged.IsBound())
	{
		EStateType Prev = Type;
		Type = InNewType;

		OnStateTypeChanged.Broadcast(Prev, InNewType);
	}
}



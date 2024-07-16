#include "CActionComponent.h"

UCActionComponent::UCActionComponent()
{
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCActionComponent::SetUnarmedMode()
{
	ChangeMode(EActionType::UnArmed);
}

void UCActionComponent::SetSwordMode()
{
	SetMode(EActionType::Sword);
}

void UCActionComponent::SetARMode()
{
	SetMode(EActionType::AR);
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
	EActionType Pre = Type;
	Type = InNextType;
}

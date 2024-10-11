#include "CAttributeComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	MaxHealth = 100.f;

	WalkSpeed[(int32)ESpeedType::Sneak] = 200;
	WalkSpeed[(int32)ESpeedType::Walk] = 400;
	WalkSpeed[(int32)ESpeedType::Sprint] = 600;

	bCanMove = true;
}


void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UCAttributeComponent::SetWalkSpeed(ESpeedType InWalkSpeed)
{
	UCharacterMovementComponent* Movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(Movement);

	Movement->MaxWalkSpeed = WalkSpeed[(int32)InWalkSpeed] - 50.f;
}

void UCAttributeComponent::OnIncreseHealth(float InHeal)
{
	CurrentHealth += InHeal;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}

void UCAttributeComponent::OnDecreseHealth(float InDeal)
{
	CurrentHealth -= InDeal;
	//FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}



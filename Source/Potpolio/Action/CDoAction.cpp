#include "CDoAction.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "GameFramework/PlayerController.h"
#include "AI/CAIController.h"


ACDoAction::ACDoAction()
{
	bAiming = false;
}

void ACDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);
	
	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	CheckNull(StateComp);

	ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	CheckNull(ActionComp);

	AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(OwnerCharacter);
	CheckNull(AttributeComp);

	PC = OwnerCharacter->GetController<APlayerController>();
	AIC = OwnerCharacter->GetController<ACAIController>();
	 
	Super::BeginPlay();
	
}

void ACDoAction::SetActionData(const TArray<FDoActionData>& InData)
{
	Data = InData;
}

void ACDoAction::SetSubActionData(const FSubActionData InData)
{
	SubData = InData;
}


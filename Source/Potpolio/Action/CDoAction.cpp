#include "CDoAction.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CActionComponent.h"
#include "GameFramework/PlayerController.h"


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

	PC = OwnerCharacter->GetController<APlayerController>();
	 
	Super::BeginPlay();
	
}

void ACDoAction::SetActionData(const TArray<FDoActionData>& InData)
{
	Data = InData;
}


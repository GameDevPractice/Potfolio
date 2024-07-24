#include "CDoAction.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Component/CStateComponent.h"

ACDoAction::ACDoAction()
{

}

void ACDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);
	
	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	CheckNull(StateComp);

	Super::BeginPlay();
	
}

void ACDoAction::SetActionData(const TArray<FDoActionData>& InData)
{
	Data = InData;
}


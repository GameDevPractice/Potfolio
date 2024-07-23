#include "CDoAction.h"
#include "Global.h"
#include "Gameframework/Character.h"

ACDoAction::ACDoAction()
{

}

void ACDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);
	Super::BeginPlay();
	
}

void ACDoAction::SetActionData(const TArray<FDoActionData>& InData)
{
	Data = InData;
}


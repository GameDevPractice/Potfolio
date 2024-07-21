#include "CDoAction.h"
#include "Global.h"
#include "Gameframework/Character.h"

ACDoAction::ACDoAction()
{

}

void ACDoAction::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDoAction::DoAction()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);
	OwnerCharacter->PlayAnimMontage(Data.AnimMontage,Data.PlayRate,Data.StartSection);
}

void ACDoAction::SetActionData(FDoActionData InData)
{
	Data = InData;
}


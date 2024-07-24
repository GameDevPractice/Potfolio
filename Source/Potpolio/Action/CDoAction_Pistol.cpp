#include "CDoAction_Pistol.h"
#include "Global.h"
#include "Aim.h"
#include "Component/CStateComponent.h"


ACDoAction_Pistol::ACDoAction_Pistol()
{

}

void ACDoAction_Pistol::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Pistol::DoAction()
{
	StateComp->SetActionMode();
}

void ACDoAction_Pistol::SubDoAction()
{
	Aim->OffAim();
}


void ACDoAction_Pistol::End_DoAction()
{
	StateComp->SetIdleMode();
}

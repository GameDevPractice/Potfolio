#include "PotpolioGameModeBase.h"
#include "Global.h"
#include "CHUD.h"



APotpolioGameModeBase::APotpolioGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn>PlayerAsset(TEXT("/Game/Player/BP_CPlayer"));
	if (PlayerAsset.Succeeded())
	{
		DefaultPawnClass = PlayerAsset.Class;
	}
	CHelpers::GetClass<AHUD>(&HUDClass, "Blueprint'/Game/UI/BP_CHUD.BP_CHUD_C'");
}
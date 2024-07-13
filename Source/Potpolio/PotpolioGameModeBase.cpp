#include "PotpolioGameModeBase.h"



APotpolioGameModeBase::APotpolioGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn>PlayerAsset(TEXT("/Game/Player/BP_CPlayer"));
	if (PlayerAsset.Succeeded())
	{
		DefaultPawnClass = PlayerAsset.Class;
	}
}
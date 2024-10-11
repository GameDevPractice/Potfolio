#include "PotpolioGameModeBase.h"
#include "Global.h"
#include "CHUD.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"



APotpolioGameModeBase::APotpolioGameModeBase()
{
	VictoryItem = 0;

	ConstructorHelpers::FClassFinder<APawn>PlayerAsset(TEXT("/Game/Player/BP_CPlayer"));
	if (PlayerAsset.Succeeded())
	{
		DefaultPawnClass = PlayerAsset.Class;
	}
	CHelpers::GetClass<AHUD>(&HUDClass, "Blueprint'/Game/UI/BP_CHUD.BP_CHUD_C'");

	ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Game/UI/WB_Win"));
	if (WidgetClass.Succeeded())
	{
		WinWidget = CreateWidget(GetWorld(), WidgetClass.Class);
		
	}
}

void APotpolioGameModeBase::IncreaseVictory()
{
	VictoryItem++;
	if (VictoryItem >= 4)
	{
		WinWidget->AddToViewport();
		WinWidget->SetVisibility(ESlateVisibility::Visible);
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(UGameplayStatics::GetPlayerController(GetWorld(),0));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0.0f);
	}
}
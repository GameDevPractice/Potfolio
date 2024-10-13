#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PotpolioGameModeBase.generated.h"

class ULevelSequence;

UCLASS()
class POTPOLIO_API APotpolioGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APotpolioGameModeBase();

public:
	UFUNCTION(BlueprintPure)
	const int32 GetVictoryItem() { return VictoryItem; }

	UFUNCTION(BlueprintCallable)
	void IncreaseVictory();

private:
	int32 VictoryItem;


protected:
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* WinWidget;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayEnding();
};

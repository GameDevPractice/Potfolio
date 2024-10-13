#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"


class UUserWidget;


UCLASS()
class POTPOLIO_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACHUD();

protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

public:
	void VisibleAim();
	void InVisibleAim();


private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrossHairTexture;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BulletWidget;

	UUserWidget* BulletCountWidget;
	 
	
	bool bVisibleAim;
	
};

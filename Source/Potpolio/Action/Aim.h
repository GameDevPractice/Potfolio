#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Aim.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACHUD;

UCLASS()
class POTPOLIO_API UAim : public UObject
{
	GENERATED_BODY()

public:
	UAim();

public:
	void BeginPlay(ACharacter* InCharacter);
	void Tick(float DeltaTime);
	void SetVisiblity(bool IsVisiblity);
	void SetHUD(ACharacter* InCharacter);

private:
	void OnAim();
	void OffAim();

private:
	ACharacter* OwnerCharacter;
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	ACHUD* HUD;
	bool bZoom;
};

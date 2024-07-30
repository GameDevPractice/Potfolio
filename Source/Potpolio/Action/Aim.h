#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Aim.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UUserWidget;

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

private:
	void OnAim();
	void OffAim();

private:
	ACharacter* OwnerCharacter;
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	TSubclassOf<UUserWidget> CrossHairclass;
	UUserWidget* CrossHair;
	

	bool bZoom;
};

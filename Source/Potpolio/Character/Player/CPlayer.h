#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"


UCLASS()
class POTPOLIO_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};

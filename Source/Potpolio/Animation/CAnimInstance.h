#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Component/CActionComponent.h"
#include "CAnimInstance.generated.h"

class ACharacter;
class UCActionComponent;
class ACDoAction;

UCLASS()
class POTPOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

	UFUNCTION()
	void ONAimChanged(bool InbAim);

protected:
	

	UPROPERTY(BlueprintReadOnly, Category = "Blend")
	float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "Blend")
	bool bFalling;
	UPROPERTY(BlueprintReadOnly, Category = "Blend")
	float Jump;
	UPROPERTY(BlueprintReadOnly, Category = "Blend")
	FRotator Rotator;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "BlendSpace")
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Blend")
	bool bAiming;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ActionType")
	EActionType ActionType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bJog;

};

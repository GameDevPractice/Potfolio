#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class ACharacter;

UCLASS()
class POTPOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	//UpdateAnimation
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	ACharacter* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Blend")
	float Speed;
	
};

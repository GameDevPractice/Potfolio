#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Component/CActionComponent.h"
#include "CStealTakeDownInterface.generated.h"

USTRUCT(BlueprintType)
struct FStealthTakeDown : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EActionType Type;

	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};

USTRUCT(BlueprintType)
struct FEnemyStealthTakeDown : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EActionType Type;

	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCStealTakeDownInterface : public UInterface
{
	GENERATED_BODY()
};

class POTPOLIO_API ICStealTakeDownInterface
{
	GENERATED_BODY()

public:

protected:
	virtual void StealTakeDown(bool InCrouch, EActionType InActionType) {}
};

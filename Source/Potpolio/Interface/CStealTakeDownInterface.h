#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Component/CActionComponent.h"
#include "CStealTakeDownInterface.generated.h"

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

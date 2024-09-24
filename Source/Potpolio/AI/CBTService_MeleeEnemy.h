#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_MeleeEnemy.generated.h"

UCLASS()
class POTPOLIO_API UCBTService_MeleeEnemy : public UBTService
{
	GENERATED_BODY()
public:
	UCBTService_MeleeEnemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Component/CAttributeComponent.h"
#include "CBTTaskNode_Speed.generated.h"

UCLASS()
class POTPOLIO_API UCBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()

	public:
		UCBTTaskNode_Speed();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	ESpeedType WalkType;
	
};

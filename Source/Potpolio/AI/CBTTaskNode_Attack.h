#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Attack.generated.h"

UCLASS()
class POTPOLIO_API UCBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()

	public:
		UCBTTaskNode_Attack();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};

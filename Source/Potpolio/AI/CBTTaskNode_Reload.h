#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Reload.generated.h"

UCLASS()
class POTPOLIO_API UCBTTaskNode_Reload : public UBTTaskNode
{
	GENERATED_BODY()

	public:
		UCBTTaskNode_Reload();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};

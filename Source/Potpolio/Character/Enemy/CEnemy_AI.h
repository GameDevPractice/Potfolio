#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/CEnemy.h"
#include "CEnemy_AI.generated.h"

class UBehaviorTree;
class UCPatrolComponent;

UCLASS()
class POTPOLIO_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_AI();

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCPatrolComponent* PatrolComp;
	
};

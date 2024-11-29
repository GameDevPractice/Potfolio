#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class ACEnemy_AI;
class UCBehaviorComponent;


UCLASS()
class POTPOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }
	UCBehaviorComponent* GetBehaviorComp() { return BehaviorComp; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly)
		UCBehaviorComponent* BehaviorComp;

private:
	UPROPERTY(EditAnywhere)
		float BehaviorRange;

	UPROPERTY(EditAnywhere)
		bool bDrawRange;

	UPROPERTY(EditDefaultsOnly)
		int32 Segment;

private:
	ACEnemy_AI* OwnerEnemy;

	UPROPERTY(EditAnywhere)
	UAISenseConfig_Sight* Sight;


	
};

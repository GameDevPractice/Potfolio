#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;
class ACPlayer;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approch, Action, Patrol, Hitted, Escape, Reload
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetBlackBoard(UBlackboardComponent* InBlackBoardComp);

	//return bool Type
public:
	UFUNCTION(BlueprintPure)
		bool IsWaitMode();
	UFUNCTION(BlueprintPure)
		bool IsApprochMode();
	UFUNCTION(BlueprintPure)
		bool IsActionMode();
	UFUNCTION(BlueprintPure)
		bool IsPatrolMode();
	UFUNCTION(BlueprintPure)
		bool IsHittedMode();
	UFUNCTION(BlueprintPure)
		bool IsEscapeMode();
	UFUNCTION(BlueprintPure)
		bool ISReloadMode();

public:
	void SetWaitMode();
	void SetApprochMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetEscapeMode();
	void SetReloadMode();

	ACPlayer* GetPlayerKey();
	FVector GetLocationKey();

private:
	void ChangeType(EBehaviorType NewType);
	EBehaviorType GetType();

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName BehaviorKey;

	//Read Only
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName PlayerKey;

	//EQS, Read Only
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName LocationKey;


private:
	UBlackboardComponent* BlackboardComp;
		
};

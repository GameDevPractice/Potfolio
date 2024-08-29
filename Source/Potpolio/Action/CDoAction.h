#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CDoAction.generated.h"



class UCStateComponent;
class UCActionComponent;
class UCActionData;
class APlayerController;
class ACAIController;


 
UCLASS()
class POTPOLIO_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() {};
	virtual void SubDoAction(bool InbAiming) {};
	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};

	FORCEINLINE bool GetbAiming() {  return bAiming; }

public:
	void SetActionData(const TArray<FDoActionData>& InData);

protected:
	TArray<FDoActionData> Data;
	ACharacter* OwnerCharacter;
	UCStateComponent* StateComp;
	UCActionComponent* ActionComp;

	APlayerController* PC;
	ACAIController* AIC;
	bool bAiming;

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CDoAction.generated.h"

class UCStateComponent;
 
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
	virtual void SubDoAction() {};
	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};

public:
	void SetActionData(const TArray<FDoActionData>& InData);

protected:
	TArray<FDoActionData> Data;
	ACharacter* OwnerCharacter;
	UCStateComponent* StateComp;

};

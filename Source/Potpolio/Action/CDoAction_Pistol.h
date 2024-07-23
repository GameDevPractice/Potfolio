#pragma once

#include "CoreMinimal.h"
#include "Action/CDoAction.h"
#include "CDoAction_Pistol.generated.h"

class UAim;

UCLASS()
class POTPOLIO_API ACDoAction_Pistol : public ACDoAction
{
	GENERATED_BODY()

public:
	ACDoAction_Pistol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void SubDoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	

private:
	UAim* Aim;
};

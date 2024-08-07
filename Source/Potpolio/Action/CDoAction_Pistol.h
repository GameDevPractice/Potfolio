#pragma once

#include "CoreMinimal.h"
#include "Action/CDoAction.h"
#include "CDoAction_Pistol.generated.h"

class ACbullet;
class UCActionData;
class ACAttachment;
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
	virtual void SubDoAction(bool InbAiming) override;
	
private:
	UFUNCTION()
	void OnBulletBeginOverlap(FHitResult InHitResult);

private:
	void DecreaseBullet();

private:

	ACbullet* Bullet;
	UCActionData* ActionData;
	ACAttachment* Attachment;

	UAim* Aim;

	int32 MaxBulletCount;
	int32 CurrentBulletCount;

};

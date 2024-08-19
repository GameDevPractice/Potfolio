#pragma once

#include "CoreMinimal.h"
#include "Action/CDoAction.h"
#include "CDoAction_Rifle.generated.h"

class ACbullet;
class UCAction;
class ACAttachment;
class UCMontageComponent;
class USoundBase;

UCLASS()
class POTPOLIO_API ACDoAction_Rifle : public ACDoAction
{
	GENERATED_BODY()
	
public:
	ACDoAction_Rifle();
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetCurrentBulletCount() { return CurrentBulletCount; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetMaxBulletCount() { return MaxBulletCount; }

private:
	UFUNCTION()
		void OnBulletBeginOverlap(FHitResult InHitResult);

public:
	void OnReload();

private:
	void OnFire();


private:
	ACbullet* Bullet;
	UCMontageComponent* MontageComp;
	UCAction* ActionData;
	ACAttachment* Attachment;
	int32 CurrentBulletCount;
	int32 MaxBulletCount;
	USoundBase* ReloadSound;
	USoundBase* AimSound;
	
};

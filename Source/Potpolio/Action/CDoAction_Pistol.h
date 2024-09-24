#pragma once

#include "CoreMinimal.h"
#include "Action/CDoAction.h"
#include "CDoAction_Pistol.generated.h"

class ACbullet;
class UCAction;
class ACAttachment;
class UAim;
class UCMontageComponent;
class USoundBase;

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

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxBulletCount;


private:
	
	UCMontageComponent* MontageComp;
	UAim* Aim;
	UCAction* ActionData;
	ACAttachment* Attachment;
	int32 CurrentBulletCount;

	int32 ReloadBullet;
	USoundBase* ReloadSound;
	USoundBase* AimSound;

};

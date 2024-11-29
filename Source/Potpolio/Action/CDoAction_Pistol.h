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
	FORCEINLINE bool CanReload() { return(MaxBulletCount > 0 ? true : false); }

	UFUNCTION(BlueprintCallable, Category = "AIm")
	void SetAimBeginPlay();
	
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

	UPROPERTY()
	UAim* Aim;
	UPROPERTY()
	UCAction* ActionData;
	UPROPERTY()
	ACAttachment* Attachment;

	int32 CurrentBulletCount;
	int32 ReloadBullet;


	UPROPERTY()
	USoundBase* ReloadSound;

	UPROPERTY()
	USoundBase* AimSound;

};

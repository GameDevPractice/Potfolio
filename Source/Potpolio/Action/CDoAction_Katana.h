#pragma once

#include "CoreMinimal.h"
#include "Action/CDoAction.h"
#include "CDoAction_Katana.generated.h"

UCLASS()
class POTPOLIO_API ACDoAction_Katana : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;

public:
	void EnableCombo();
	void DisableCombo();
	void ClearHittedCharacter();

private:
	void Begin_DoAction();
	void End_DoAction();

public:
	virtual void OnAttachBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter, UPrimitiveComponent* Component) override;
	virtual void OnAttachEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;
	

private:
	int32 ComboCount = 0;
	bool bcanCombo = false;
	bool bSuccessCombo = false;
	TArray<ACharacter*> HittedCharacters;
	bool bFinalAttack = false;
};

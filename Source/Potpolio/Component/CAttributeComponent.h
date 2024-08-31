#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Sneak, Walk, Sprint, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAttributeComponent();

protected:
	virtual void BeginPlay() override;
public:
	FORCEINLINE bool IsMove() {return bCanMove;}

	//Health
	FORCEINLINE float GetMaxHealth() {return MaxHealth;}
	FORCEINLINE float GetCurrentHealth() {return CurrentHealth;}

	//WalkSpeed
	FORCEINLINE float GetSneakpeed() {return WalkSpeed[(int32)ESpeedType::Sneak];}
	FORCEINLINE float GetWalkpeed() {return WalkSpeed[(int32)ESpeedType::Walk];}
	FORCEINLINE float GetSprintpeed() {return WalkSpeed[(int32)ESpeedType::Sprint];}

	void SetWalkSpeed(ESpeedType InWalkSpeed);

public:
	//Health Func
	void OnIncreseHealth(float InHeal);
	void OnDecreseHealth(float InDeal);

	//Move Func
	void SetMove();
	void SetStop();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		float MaxHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		float WalkSpeed[(int32)ESpeedType::Max];

private:
	bool bCanMove;
	float CurrentHealth;


		
};

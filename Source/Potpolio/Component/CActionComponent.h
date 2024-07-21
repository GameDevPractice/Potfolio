#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	UnArmed, Sword, Pistol,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	//���� ���°� �������� Ȯ���ϴ� �Լ���
	FORCEINLINE bool IsUnarmedMode() { return (Type == EActionType::UnArmed); }
	FORCEINLINE bool IsSwordMode() { return (Type == EActionType::Sword); }
	FORCEINLINE bool IsPistolMode() { return (Type == EActionType::Pistol); }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE UCActionData* GetCurrentActionData() { return DataAssets[(int32)Type]; }
		FORCEINLINE bool IsCanUnArm() { return CanUnArm; }

public:
	//���� �����ϴ� �Լ� (�ܺ�)
	void SetUnarmedMode();
	void SetSwordMode();
	void SetPistolMode();

private:
	void SetMode(EActionType InNextType);
	void ChangeMode( EActionType InNextType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;
	bool CanUnArm;
		
};

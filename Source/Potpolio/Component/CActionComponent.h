#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"


class UCActionData;
class UCAction;

UENUM(BlueprintType)
enum class EActionType : uint8
{
	UnArmed, Sword, Pistol,Rifle,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAimChanged, bool, bAiming);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ResetBeginplay();

public:
	//���� ���°� �������� Ȯ���ϴ� �Լ���
	FORCEINLINE bool IsUnarmedMode() { return (Type == EActionType::UnArmed); }
	FORCEINLINE bool IsSwordMode() { return (Type == EActionType::Sword); }
	FORCEINLINE bool IsPistolMode() { return (Type == EActionType::Pistol); }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsRifleMode() { return (Type == EActionType::Rifle); }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE UCActionData* GetCurrentActionData() { return DataAssets[(int32)Type]; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE UCAction* GetCurrentAction() { return Datas[(int32)Type]; }
		FORCEINLINE EActionType GetCurrentType() { return NextType; }
		FORCEINLINE bool IsCanUnArm() { return CanUnArm; }
		FORCEINLINE bool IsCanChange() { return CanChange; }


public:
	void DoAction();
	void DoSubAction(bool InbAiming);
	void Abort();
	void ChangeEquip(EActionType InNextType);

public:
	//���� �����ϴ� �Լ� (�ܺ�)
	UFUNCTION(BlueprintCallable)
	void SetUnarmedMode();
	UFUNCTION(BlueprintCallable)
	void SetSwordMode();
	UFUNCTION(BlueprintCallable)
	void SetPistolMode();
	UFUNCTION(BlueprintCallable)
	void SetRifleMode();

private:
	void SetMode(EActionType InNextType);
	void ChangeMode( EActionType InNextType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

	UPROPERTY(BlueprintAssignable)
		FAimChanged ONAimChanged;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	EActionType NextType;
	bool CanUnArm;
	bool CanChange;

	UPROPERTY()
	UCAction* Datas[(int32)EActionType::Max];
		
};

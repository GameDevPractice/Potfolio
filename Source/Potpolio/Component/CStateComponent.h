#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"


//상태를 ENum으로 저장
UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Jump, Parkour,Reload ,Equip,UnEquip ,Action,Hitted, Dead,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPreType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

	//InLine Func
public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsJumpMode() { return Type == EStateType::Jump; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsUnEquipMode() { return Type == EStateType::UnEquip; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsReloadMode() { return Type == EStateType::Reload; }

public:
	void SetIdleMode();
	void SetJumpMode();
	void SetEquipMode();
	void SetUnEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetReloadMode();

private:
	void ChangeMode(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;


	//현재 상태를 저장할 변수
public:
	EStateType Type;


		
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	UnArmed, Sword, AR, Pistol, Max
};

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
	FORCEINLINE bool ISUnarmedMode() { return (Type == EActionType::UnArmed); }
	FORCEINLINE bool IsSwordMode() { return (Type == EActionType::Sword); }
	FORCEINLINE bool IsARMode() { return (Type == EActionType::AR); }
	FORCEINLINE bool IsPistolMode() { return (Type == EActionType::Pistol); }

public:
	//���� �����ϴ� �Լ� (�ܺ�)
	void SetUnarmedMode();
	void SetSwordMode();
	void SetARMode();
	void SetPistolMode();

private:
	void SetMode(EActionType InNextType);
	void ChangeMode( EActionType InNextType);

private:
	EActionType Type;

		
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Component/CStateComponent.h"
#include "CMontageComponent.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EStateType Type;

	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate;

	UPROPERTY(EditAnywhere)
	FName StartSection;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTPOLIO_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayReload();
	void PlayHitted();
	void PlayDead();
	void PlayEvade();

private:
	void PlayAnimMontage(EStateType NewType);

private:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

private:
	FMontageData* Datas[(int32)EStateType::Max];

		
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Component/CStateComponent.h"
#include "Component/CActionComponent.h"
#include "Interface/CStealTakeDownInterface.h"
#include "CEnemy.generated.h"

class UCActionComponent;
class UCMontageComponent;
class UCStateComponent;
class UCAttributeComponent;
class USkeletalMesh;
class AAIController;
class UWidgetComponent;
class UCWorldWidget;
class UBoxComponent;

USTRUCT(BlueprintType)
struct FEnemyStealthTakeDown : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EActionType Type;

	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS()
class POTPOLIO_API ACEnemy : public ACharacter, public ICStealTakeDownInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

	void StealTakeDown(bool InCrouch, EActionType InActionType) override;

protected:
	UFUNCTION()
		void OnStateTypeChanged(EStateType PreType, EStateType NewType);

	UFUNCTION()
		void OnTakeDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OffTakeDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void EndTakeDown();

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	void EnemyDestroy();

private:
	void Hitted();
	void Dead();


public:
	void TagetWidgetOn();
	void TagetWidgetOff();

	void TakeDown(bool InCrouch, EActionType InType);

private:
	//StealthTakeDown
	void OnStandingSword(bool InCrouch,EActionType InType);
	void OnCrounhSword(bool InCrouch,EActionType InType);
	void OnStandingUnArmed(bool InCrouch,EActionType InType);



protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCActionComponent* ActionComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCMontageComponent* MontageComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UBoxComponent* BoxComp;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCWorldWidget> TakeOverClass;

	UCWorldWidget* TakeOverWidget;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "TakeDown")
		UAnimMontage* TakeDownMontage;


private:
	float DamageValue;
	AController* DamageInstigator;

	AAIController* AIC;

	//TakeDown
	FTimerHandle TakeDownHandle;

private:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

	FEnemyStealthTakeDown* StealthTakeDownData[(int32)EActionType::Max];


};
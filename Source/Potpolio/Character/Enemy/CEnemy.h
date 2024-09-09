#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
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


UCLASS()
class POTPOLIO_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

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

	void TakeDown();



protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCMontageComponent* MontageComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCStateComponent* StateComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UBoxComponent* BoxComp;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCWorldWidget> TargetWidgetClass;

	UCWorldWidget* TargetWidget;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "TakeDown")
		UAnimMontage* TakeDownMontage;


private:
	float DamageValue;
	AController* DamageInstigator;

	AAIController* AIC;

	//TakeDown
	FTimerHandle TakeDownHandle;


};
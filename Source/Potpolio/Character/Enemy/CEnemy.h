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

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	void Hitted();
	void Dead();


public:
	void TagetWidgetOn();
	void TagetWidgetOff();



protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCMontageComponent* MontageComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCStateComponent* StateComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCAttributeComponent* AttributeComp;



protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCWorldWidget> TargetWidgetClass;

	UCWorldWidget* TargetWidget;


private:
	float DamageValue;
	AController* DamageInstigator;

	AAIController* AIC;


};
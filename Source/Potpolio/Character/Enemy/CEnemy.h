#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

class UCActionComponent;
class UCMontageComponent;
class UCStateComponent;
class UCAttributeComponent;
class USkeletalMesh;

UCLASS()
class POTPOLIO_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCMontageComponent* MontageComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCStateComponent* StateComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCAttributeComponent* AttributeComp;

};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMesh;
class UMaterialInstanceDynamic;
class USkeletalMeshComponent;
class UCActionComponent;
class UCMontageComponent;
class UCStateComponent;
class UCAttributeComponent;

UCLASS()
class POTPOLIO_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnLockUp(float Axix);
	void OnLockRight(float Axix);

	void OnRun();
	void OnWalk();

	void OnSword();
	void OnPistol();
	void OnPrimaryAct();
	void OnSecondaryAct();
	void OffSecondaryAct();

	void OnJump();

	void OnReload();
	void Begin_Reload();

public:
	void End_Jump();
	void End_Parkour();
	void End_Reload();



	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
		void OnStateTypeChanged(EStateType PreType, EStateType NewType);



private:
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	UMaterialInstanceDynamic* HandsKatanaMat;
	UMaterialInstanceDynamic* CostumeMat;
	UMaterialInstanceDynamic* HeadMat;
	UMaterialInstanceDynamic* EyeMat;
	UMaterialInstanceDynamic* HairMat;
	UMaterialInstanceDynamic* PantsMat;
	UMaterialInstanceDynamic* JacketMat;

	TArray<UMaterialInstanceDynamic*> Materials;

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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "GenericTeamAgentInterface.h"
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
class ACEnemy;


UCLASS()
class POTPOLIO_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaSeconds) override;

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

	void Target_On();

	void OnJog();

public:
	void End_Jump();
	void End_Parkour();
	void End_Reload();

	void OnTakeDown();
	void OffTakeDown();

	FORCEINLINE bool GetJog() { return bJog; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	UFUNCTION()
	void OnStateTypeChanged(EStateType PreType, EStateType NewType);
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
		void OnStartRun();

	UFUNCTION()
	void EndTakeDown();

	UFUNCTION()
		void EndVault();
private:
	void Hitted();
	void TakeDown();



private:


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
	USpringArmComponent* SpringArmComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
	UCameraComponent* CameraComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		UCActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UCMontageComponent* MontageComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UCStateComponent* StateComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCAttributeComponent* AttributeComp;



private:
	UPROPERTY(EditDefaultsOnly, Category = "TeamID")
		uint8 TeamID;

private:
	float DamageValue;
	AController* DamageInstigator;

	FTimerHandle RunTimer;

private:
	//TagetActor
	TArray<AActor*> TargetActors;
	ACEnemy* MostLearestActor;
	ACEnemy* LockOnTarget;

	float TargetMax;

	//TakeDown
	bool CanStealthTakeDown;
	UPROPERTY(EditDefaultsOnly, Category = "StealthTakeDown")
	UAnimMontage* StealthTakeDownMontage;
	FTimerHandle StealthTakeDownHandle;
	ACameraActor* StealthTakeDownCamera;

	//Jog
	bool bJog;

	//Vault
	bool bRun;
};

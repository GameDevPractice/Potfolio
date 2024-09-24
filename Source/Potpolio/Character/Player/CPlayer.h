#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Component/CStateComponent.h"
#include "GenericTeamAgentInterface.h"
#include "Component/CActionComponent.h"
#include "Interface/CStealTakeDownInterface.h"
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

USTRUCT(BlueprintType)
struct FStealthTakeDown : public FTableRowBase
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
class POTPOLIO_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface, public ICStealTakeDownInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaSeconds) override;

	void StealTakeDown(bool InCrouch, EActionType InActionType) override;

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

	void OnSwordStealthTakeDown(bool InCrouch,EActionType InActionType);
	void OnSwordCrouchStealthTakeDown(bool InCrouch,EActionType InActionType);
	void OnUnArmdStandingStealthTakeDown(bool InCrouch, EActionType InActionType);

public:
	void End_Jump();
	void End_Parkour();
	void End_Reload();

	void OnTakeDown();
	void OffTakeDown();

	void OnBlockBox();
	void OffBlockBox();

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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
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
	FTimerHandle StealthTakeDownHandle;
	ACameraActor* StealthTakeDownCamera;

	//UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HealthWidgetClass;

	public:
		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "UI")
		UUserWidget* HealthWidget;

private:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

	FStealthTakeDown* StealthTakeDownData[(int32)EActionType::Max];

	//Jog
	bool bJog;

	//Vault
	bool bRun;
};

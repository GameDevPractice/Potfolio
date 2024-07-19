#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Action/CActionData.h"
#include "CEquipment.generated.h"

class UCStateComponent;
class UCAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE (FUnequipmentDelegate);

UCLASS()
class POTPOLIO_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	void SetData(const FEquipData& InData);
	

public:
	//Equip & UnEquip Func
	UFUNCTION(BlueprintNativeEvent)
	void Equip();
	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();
	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();
	UFUNCTION(BlueprintNativeEvent)
	void UnEquip();

public:
	//Delegate Equip, UnEquip
	UPROPERTY(BlueprintAssignable)
		FEquipmentDelegate OnEquipmentDelegate;
	UPROPERTY(BlueprintAssignable)
		FUnequipmentDelegate OnUnequipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
		ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
		UCAttributeComponent* AttributeComp;
private:
	FEquipData Data;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class UParticleSystem;
class ACharacter;
class ACEquipment;
class ACAttachment;
class ACDoAction;

//������ ���� �����͵�
USTRUCT(BlueprintType)
struct FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly)
		float PlayRate = 1.f;

	UPROPERTY(EditDefaultsOnly)
		FName StartSection;
};

USTRUCT(BlueprintType)
struct FUnEquipData : public FEquipData
{
	GENERATED_BODY()
};

//�ൿ�� ���� �����͵�
USTRUCT(BlueprintType)
struct FDoActionData : public FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float Power;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* Particle;

	UPROPERTY(EditDefaultsOnly)
	FTransform EffectTransforms;
};

UCLASS()
class POTPOLIO_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InOwnerCharacter);

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }

public:
	//Equipment Data
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		FEquipData EquipData;

	UPROPERTY(EditDefaultsOnly, Category = "UnEquipment")
		FUnEquipData UnEquipData;

	//Attachment Data
	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		TSubclassOf<ACAttachment> AttachmentClass;

	//DoAction Data
	UPROPERTY(EditDefaultsOnly, Category = "DoAction")
		TSubclassOf<ACDoAction> DoActionClass;
	UPROPERTY(EditDefaultsOnly, Category = "DoAction")
		FDoActionData DoActionData;
private:
	ACEquipment* Equipment;
	ACAttachment* Attachment;
	ACDoAction* DoAction;
};
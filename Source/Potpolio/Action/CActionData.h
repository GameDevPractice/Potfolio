#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class UParticleSystem;
class ACharacter;
class ACEquipment;
class ACAttachment;

//장착에 관한 데이터들
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

//행동에 관한 데이터들
//USTRUCT(BlueprintType)
//struct FDoActionData : public FEquipData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditDefaultsOnly)
//	float Power;
//
//	UPROPERTY(EditDefaultsOnly)
//	UParticleSystem* Particle;
//
//	UPROPERTY(EditDefaultsOnly)
//	FTransform EffectTransforms;
//};

UCLASS()
class POTPOLIO_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InOwnerCharacter);

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }

public:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		FEquipData EquipData;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<ACAttachment> AttachmentClass;
private:
	ACEquipment* Equipment;
	ACAttachment* Attachment;
};

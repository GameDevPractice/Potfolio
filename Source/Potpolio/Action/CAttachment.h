#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

class ACharacter;
class USkeletalMeshComponent;
class UParticleSystem;
class USoundBase;
class UShapeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, ACharacter*, InAttacker, AActor*, InCauser, ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap, ACharacter*, InAttacker, AActor*, InCauser, ACharacter*, InOtherCharacter);

UCLASS()
class POTPOLIO_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	 FORCEINLINE USkeletalMeshComponent* GetMesh() { return Mesh; }
	 FORCEINLINE UParticleSystem* GetParticle() { return ParticleComp; }
	 FORCEINLINE USoundBase* GetSound() { return Sound; }

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnEquip();

	void OnCollisions();
	void OffCollisions();

protected:
	UFUNCTION(BlueprintCallable)
		void ActorAttachTo(FName InSocketName);

private:
	UFUNCTION()
		void OnComponentBeingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintAssignable)
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	UPROPERTY(BlueprintAssignable)
	FAttachmentEndOverlap OnAttachmentEndOverlap;
private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
	UParticleSystem* ParticleComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* Sound;

protected:
	UPROPERTY(BlueprintReadOnly)
		ACharacter* OwnerCharacter;

private:
	TArray<UShapeComponent*> Collisions;



};

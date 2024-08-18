#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cbullet.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class USphereComponent;
class UMaterialInstanceConstant;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletBeginOverlap, FHitResult, InHitResult);

UCLASS()
class POTPOLIO_API ACbullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACbullet();

protected:
	 void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
	FBulletBeginOverlap OnBulletBeginOverlap;

private:
	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly)
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileComp;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Decal")
		UMaterialInstanceConstant* Decal;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cbullet.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class USphereComponent;


UCLASS()
class POTPOLIO_API ACbullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACbullet();

protected:
	 void BeginPlay() override;


private:
	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileComp;
};

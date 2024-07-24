#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cbullet.generated.h"


class UStaticMeshComponent;
class UProjectileMovementComponent;
class UMaterialInstanceConstant;


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
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstanceConstant* Material;;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileComp;
};

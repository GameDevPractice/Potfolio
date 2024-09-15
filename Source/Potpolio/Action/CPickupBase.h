#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPickupBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class POTPOLIO_API ACPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPickupBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComp;
};

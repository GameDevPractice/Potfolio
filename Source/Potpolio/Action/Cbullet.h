#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cbullet.generated.h"

class UStaticMeshComponent;

UCLASS()
class POTPOLIO_API ACbullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACbullet();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
		UStaticMeshComponent* Bullet;

};

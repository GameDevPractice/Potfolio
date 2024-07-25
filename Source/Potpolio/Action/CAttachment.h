#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

class ACharacter;
class USkeletalMeshComponent;

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

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnEquip();

protected:
	UFUNCTION(BlueprintCallable)
		void ActorAttachTo(FName InSocketName);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

protected:
	UPROPERTY(BlueprintReadOnly)
		ACharacter* OwnerCharacter;

};

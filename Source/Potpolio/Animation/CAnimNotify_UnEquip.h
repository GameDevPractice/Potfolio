#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_UnEquip.generated.h"

UCLASS()
class POTPOLIO_API UCAnimNotify_UnEquip : public UAnimNotify
{
	GENERATED_BODY()
	
		FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

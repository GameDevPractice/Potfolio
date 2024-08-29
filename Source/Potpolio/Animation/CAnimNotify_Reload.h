
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Reload.generated.h"


UCLASS()
class POTPOLIO_API UCAnimNotify_Reload : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};

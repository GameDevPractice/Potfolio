
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Hiited.generated.h"


UCLASS()
class POTPOLIO_API UCAnimNotify_Hiited : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};

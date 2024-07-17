#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndJump.generated.h"
UCLASS()
class POTPOLIO_API UCAnimNotify_EndJump : public UAnimNotify
{
	GENERATED_BODY()
	

public:
		FString GetNotifyName_Implementation() const override;
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

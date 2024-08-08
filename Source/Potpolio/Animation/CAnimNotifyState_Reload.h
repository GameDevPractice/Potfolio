#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Reload.generated.h"

UCLASS()
class POTPOLIO_API UCAnimNotifyState_Reload : public UAnimNotifyState
{
	GENERATED_BODY()

		FString GetNotifyName() const;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};

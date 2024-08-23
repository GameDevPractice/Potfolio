#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

class ACEquipment;
class ACAttachment;
class ACDoAction;

UCLASS()
class POTPOLIO_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	friend class UCActionData;

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE ACAttachment* GetAttachment() { return Attachment; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE ACDoAction* GetDoAction() { return DoAction; }

private:
	ACEquipment* Equipment;
	ACAttachment* Attachment;
	ACDoAction* DoAction;
	
};

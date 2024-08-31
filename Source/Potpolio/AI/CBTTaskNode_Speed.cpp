#include "AI/CBTTaskNode_Speed.h"
#include "Global.h"
#include "AI/CAIController.h"


UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* Pawn = AIC->GetPawn();
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UCAttributeComponent* AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(Pawn);
	if (AttributeComp)
	{
		AttributeComp->SetWalkSpeed(WalkType);
	return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

#include "AI/CBTTaskNode_Attack.h"
#include "Global.h"
#include "AI/CAIController.h"
#include "Component/CActionComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(Pawn);
	if (ActionComp)
	{
		ActionComp->DoAction();
	return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

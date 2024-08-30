#include "AI/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "AI/CAIController.h"
#include "AI/CPatrolPath.h"
#include "Component/CPatrolComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* Pawn = AIC->GetPawn();
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(Pawn);
	
	if (PatrolComp)
	{
		
		if (PatrolComp->IsPathValid() == false)
		{
			return EBTNodeResult::Failed;
		}
	}
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	APawn* Pawn = AIC->GetPawn();
	CheckNull(Pawn);
	
	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(Pawn);
	CheckNull(PatrolComp);

	FVector Location;
	PatrolComp->GetMoveTo(Location);

	EPathFollowingRequestResult::Type RequestResult = AIC->MoveToLocation(Location);

	if (RequestResult == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else if (RequestResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		PatrolComp->UpdateNextIndex();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

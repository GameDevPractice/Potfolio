#include "AI/CBTTaskNode_Reload.h"
#include "Global.h"
#include "AI/CAIController.h"
#include "Component/CActionComponent.h"
#include "Component/CMontageComponent.h"
#include "Action/CAction.h"
#include "Action/CDoAction_Rifle.h"

UCBTTaskNode_Reload::UCBTTaskNode_Reload()
{
	NodeName = "Reload";
}

EBTNodeResult::Type UCBTTaskNode_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UCMontageComponent* MontageComp = CHelpers::GetComponent<UCMontageComponent>(Pawn);
	if (ActionComp)
	{
		UCAction* Action = ActionComp->GetCurrentAction();
		if (Action)
		{
			ACDoAction_Rifle* DoActionRifle = Cast<ACDoAction_Rifle>(Action->GetDoAction());
			if (DoActionRifle)
			{
				if (MontageComp)
				{
				MontageComp->PlayReload();
				return EBTNodeResult::Succeeded;
				}
			}
		}

	}
	return EBTNodeResult::Failed;
}

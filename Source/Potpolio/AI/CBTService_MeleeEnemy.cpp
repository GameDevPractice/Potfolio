#include "AI/CBTService_MeleeEnemy.h"
#include "Global.h"
#include "AI/CAIController.h"
#include "Component/CBehaviorComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CPatrolComponent.h"
#include "Component/CActionComponent.h"
#include "Character/Enemy/CEnemy_AI.h"
#include "Character/Player/CPlayer.h"


UCBTService_MeleeEnemy::UCBTService_MeleeEnemy()
{
	NodeName = "RootEnemy";
}

void UCBTService_MeleeEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);
	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);

	ACEnemy_AI* EnemyPawn = Cast<ACEnemy_AI>(AIC->GetPawn());
	CheckNull(EnemyPawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(EnemyPawn);
	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(EnemyPawn);

	//Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();
		return;
	}

	//Get On Player from BB
	ACPlayer* Player = BehaviorComp->GetPlayerKey();

	//Check Player
	if (Player == nullptr)
	{
		AIC->ClearFocus(EAIFocusPriority::Gameplay);
		if (PatrolComp->IsPathValid())
		{
			BehaviorComp->SetPatrolMode();
			return;
		}
		BehaviorComp->SetWaitMode();
		return;
	}

	//Enemy <-> Player
	float Distance = EnemyPawn->GetDistanceTo(Player);

	if (Distance < AIC->GetBehaviorRange())
	{
		AIC->ClearFocus(EAIFocusPriority::Gameplay);
		BehaviorComp->SetActionMode();
		return;
	}

	if (Distance < AIC->GetSightRadius())
	{
		AIC->SetFocus(Player);
		BehaviorComp->SetApprochMode();
		return;
	}

}
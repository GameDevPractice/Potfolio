#include "AI/CBTService_Enemy.h"
#include "Global.h"
#include "AI/CAIController.h"
#include "Component/CBehaviorComponent.h"
#include "Component/CStateComponent.h"
#include "Character/Enemy/CEnemy_AI.h"
#include "Character/Player/CPlayer.h"


UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "RootEnemy";
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);
	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);

	ACEnemy_AI* EnemyPawn = Cast<ACEnemy_AI>(AIC->GetPawn());
	CheckNull(EnemyPawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);

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
		BehaviorComp->SetWaitMode();
		return;
	}

	//Enemy <-> Player
	float Distance = EnemyPawn->GetDistanceTo(Player);

	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetEscapeMode();
		return;
	}

	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetActionMode();
		
		return;
	}

}
#include "Character/Enemy/CEnemy_AI.h"
#include "Global.h"
#include "Component/CPatrolComponent.h"

ACEnemy_AI::ACEnemy_AI()
{

	CHelpers::CreateActorComponent(this, &PatrolComp, TEXT("PatrolComp"));
}
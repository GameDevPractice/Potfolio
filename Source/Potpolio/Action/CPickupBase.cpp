#include "Action/CPickupBase.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACPickupBase::ACPickupBase()
{
	CHelpers::CreateSceneComponent(this, &MeshComp,"MeshComp");
	RootComponent = MeshComp;
	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", MeshComp);
}

void ACPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}


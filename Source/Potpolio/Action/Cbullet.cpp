#include "Cbullet.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

ACbullet::ACbullet()
{
	CHelpers::CreateSceneComponent(this,&Bullet,"StaticComp",RootComponent);
}

void ACbullet::BeginPlay()
{
	Super::BeginPlay();
	
}



#include "Cbullet.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACbullet::ACbullet()
{
	CHelpers::CreateSceneComponent(this, &SphereComp, "SphereComp");
	CHelpers::CreateSceneComponent(this, &ParticleComp,"ParticleComp", SphereComp);
	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");

	ProjectileComp->InitialSpeed = 4000.f;
	ProjectileComp->MaxSpeed = 8000.f;
	ProjectileComp->ProjectileGravityScale = 0.0f;
}

void ACbullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(3.0f);
	
}


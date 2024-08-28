#include "Cbullet.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACbullet::ACbullet()
{
	CHelpers::CreateSceneComponent(this, &SphereComp, "SphereComp");
	CHelpers::CreateSceneComponent(this, &ParticleComp,"ParticleComp", SphereComp);
	CHelpers::GetAsset(&Decal, "/Game/Materials/MI_Decal");

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");

	InitialLifeSpan = 3.f;
	ProjectileComp->InitialSpeed = 4000.f;
	ProjectileComp->MaxSpeed = 8000.f;
	ProjectileComp->ProjectileGravityScale = 0.0f;

	SphereComp->SetCollisionProfileName("Projectile");
}



void ACbullet::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACbullet::OnComponentBeginOverlap);
}

void ACbullet::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner());
	if (OnBulletBeginOverlap.IsBound())
	{
		OnBulletBeginOverlap.Broadcast(SweepResult);
	}
	Destroy();
}


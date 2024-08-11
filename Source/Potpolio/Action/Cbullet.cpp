#include "Cbullet.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACbullet::ACbullet()
{
	CHelpers::CreateSceneComponent(this, &ParticleComp,"ParticleComp");
	CHelpers::CreateSceneComponent(this, &CapsuleComp, "CapsuleComp", ParticleComp);
	CHelpers::GetAsset(&Decal, "/Game/Materials/MI_Decal");

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");

	InitialLifeSpan = 3.f;
	ProjectileComp->InitialSpeed = 4000.f;
	ProjectileComp->MaxSpeed = 8000.f;
	ProjectileComp->ProjectileGravityScale = 0.0f;

	CapsuleComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	CapsuleComp->SetRelativeScale3D(FVector(1.f, 1.f, 0.6425f));
	CapsuleComp->SetCapsuleRadius(2.f);
	CapsuleComp->SetCapsuleHalfHeight(22.f);

	CapsuleComp->SetCollisionProfileName("Projectile");
}



void ACbullet::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACbullet::OnComponentBeginOverlap);
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


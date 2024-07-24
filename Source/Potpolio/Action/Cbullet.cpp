#include "Cbullet.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACbullet::ACbullet()
{
	CHelpers::CreateActorComponent(this, &MeshComp,"MeshComp");
	SetRootComponent(MeshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMesh/Sphere"));
	if(MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
	}
	MeshComp->SetRelativeScale3D(FVector(1.f, 0.025f, 0.025f));

	CHelpers::GetAsset(&Material,"/Game/Materials/MI_Bullet");
	MeshComp->SetMaterial(0, Material);

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


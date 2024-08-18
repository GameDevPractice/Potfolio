#include "CEnemy.h"
#include "Global.h"
#include "Component/CActionComponent.h"
#include "Component/CMontageComponent.h"
#include "Component/CAttributeComponent.h"
#include "Components/SkeletalMeshComponent.h"

ACEnemy::ACEnemy()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	USkeletalMesh* MeshComp;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Enemy/Mesh/Kachujin_G_Rosales"));
	if (MeshAsset.Succeeded())
	{
		MeshComp = MeshAsset.Object;
		GetMesh()->SetSkeletalMesh(MeshComp);
	}

	//ActionComponet
	CHelpers::CreateActorComponent(this, &ActionComp, TEXT("ActionComp"));
	//MontageComponet
	CHelpers::CreateActorComponent(this, &MontageComp, TEXT("MontageComp"));
	//StateComponent
	CHelpers::CreateActorComponent(this, &StateComp, TEXT("StateComp"));
	//AttributeComponet
	CHelpers::CreateActorComponent(this, &AttributeComp, TEXT("Attribute"));
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

}
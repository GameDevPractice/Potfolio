#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CHelpers::CreateSceneComponent(this, &Mesh, "MeshComp", RootComp);
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Super::BeginPlay();
	
}

//��� ����Ʈ���� ���, �����Ϳ���
void ACAttachment::ActorAttachTo(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

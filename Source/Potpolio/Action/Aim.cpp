#include "Aim.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CHUD.h"

UAim::UAim()
{
	bZoom = false;
}

void UAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	CheckNull(OwnerCharacter->GetController<APlayerController>());
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();
	
	HUD = PC->GetHUD<ACHUD>();
}


void UAim::SetVisiblity(bool IsVisiblity)
{
	(IsVisiblity ? OnAim() : OffAim());
}

void UAim::SetHUD(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	CheckNull(OwnerCharacter->GetController<APlayerController>());
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

	HUD = PC->GetHUD<ACHUD>();
}

void UAim::OnAim()
{
	CheckTrue(bZoom);
	CheckNull(HUD);
	bZoom = true;
	HUD->VisibleAim();

	//Camera zoom out
	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);
	SpringArmComp->bEnableCameraLag = false;

	//Rotation Character
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UAim::OffAim()
{
	CheckFalse(bZoom);

	bZoom = false;

	HUD->InVisibleAim();

	//Camera zoom out
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector::ZeroVector;
	SpringArmComp->bEnableCameraLag = false;

	//Rotation Character
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

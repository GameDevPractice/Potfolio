#include "Aim.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UAim::UAim()
{
	CHelpers::GetClass<UUserWidget>(&CrossHairclass, "/Game/UI/WB_CrossHead");
	CrossHair = CreateWidget(GetWorld(), CrossHairclass);
	bZoom = false;
}

void UAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	CrossHair->AddToViewport();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);
}


void UAim::SetVisiblity(bool IsVisiblity)
{
	(IsVisiblity ? OnAim() : OffAim());
}

void UAim::OnAim()
{
	CheckTrue(bZoom);

	bZoom = true;

	//Show Widget
	CrossHair->SetVisibility(ESlateVisibility::Visible);

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

	//hide Widget
	CrossHair->SetVisibility(ESlateVisibility::Hidden);

	//Camera zoom out
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector::ZeroVector;
	SpringArmComp->bEnableCameraLag = false;

	//Rotation Character
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

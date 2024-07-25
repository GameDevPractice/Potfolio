#include "Aim.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

UAim::UAim()
{

}

void UAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
}

void UAim::OnAim()
{

}

void UAim::OffAim()
{
	
}

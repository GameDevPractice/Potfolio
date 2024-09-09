#include "CAnimInstance.h"
#include "Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Character/Player/CPlayer.h"
#include "Component/CActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CheckNull(TryGetPawnOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(TryGetPawnOwner());

	CheckNull(ActionComp);

	ActionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
	ActionComp->ONAimChanged.AddDynamic(this, &UCAnimInstance::ONAimChanged);
	Rotator = FRotator::ZeroRotator;

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//Save Player
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Character);

	ACPlayer* Player = Cast<ACPlayer>(Character);
	if (Player)
	{
	bJog = Player->GetJog();
	}


	bFalling = Character->GetCharacterMovement()->IsFalling();

	Speed = Character->GetVelocity().Size2D();

	AController* PC = Character->GetController();
	CheckNull(PC);

	float rotation = PC->GetControlRotation().Pitch;

	Rotator.Yaw = -1 * PC->GetControlRotation().Pitch;
	
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());

}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

void UCAnimInstance::ONAimChanged(bool InbAim)
{
	if(InbAim)
	CLog::Print("On");
	bAiming = InbAim;
}

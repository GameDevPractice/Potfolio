#include "CAnimInstance.h"
#include "Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
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
	Player = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Player);

	bFalling = Player->GetCharacterMovement()->IsFalling();

	Speed = Player->GetVelocity().Size2D();

	AController* PC = Player->GetController();
	CheckNull(PC);

	float rotation = PC->GetControlRotation().Pitch;

	Rotator.Yaw = -1 * PC->GetControlRotation().Pitch;
	
	Direction = CalculateDirection(Player->GetVelocity(), Player->GetControlRotation());

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

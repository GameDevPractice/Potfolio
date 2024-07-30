#include "CAnimInstance.h"
#include "Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CheckNull(TryGetPawnOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(TryGetPawnOwner());

	CheckNull(ActionComp);

	ActionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
	ActionComp->ONAimChanged.AddDynamic(this, &UCAnimInstance::ONAimChanged);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//Save Player
	Player = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Player);

	Speed = Player->GetVelocity().Size2D();

	AController* PC = Player->GetController();
	CheckNull(PC);

	Rotator = PC->GetControlRotation();
	CLog::Print(Rotator);


}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

void UCAnimInstance::ONAimChanged(bool InbAim)
{
	bAiming = InbAim;
}

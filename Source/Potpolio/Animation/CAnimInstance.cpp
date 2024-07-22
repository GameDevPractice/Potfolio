#include "CAnimInstance.h"
#include "Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CheckNull(TryGetPawnOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(TryGetPawnOwner());

	CheckNull(ActionComp);

	ActionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//Save Player
	Player = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Player);

//Save Speed
	Speed = Player->GetVelocity().Size2D();

	Jump = Player->GetVelocity().Z;

	if (Jump <= 0)
	{
		bFalling = false;
	}
	else
	{
		bFalling = true;
	}
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

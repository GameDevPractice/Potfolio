#include "CAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Save Player
	Player = Cast<ACharacter>(TryGetPawnOwner());
	if (Player == nullptr)
	{
		return;
	}


//Save Speed
	Speed = Player->GetVelocity().Size2D();
}

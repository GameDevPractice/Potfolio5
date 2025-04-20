#include "CAnimInstance.h"
#include "Character/CPlayer.h"



void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.f;
	Direction = 0.f;
	Hight = 0.f;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	player = Cast<ACPlayer>(TryGetPawnOwner());
	if (player)
	{
		Speed = player->GetVelocity().Size2D();
		Direction = CalculateDirection(player->GetVelocity(), player->GetActorRotation());
		Hight = player->GetVelocity().Z;
	}

}

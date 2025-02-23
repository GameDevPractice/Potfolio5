#include "CAnimInstance.h"
#include "Character/CPlayer.h"



void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.f;
	Direction = 0.f;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACPlayer* Player = Cast<ACPlayer>(GetOwningActor());
	if (Player)
	{
		Speed = Player->GetVelocity().Size();
	}

}

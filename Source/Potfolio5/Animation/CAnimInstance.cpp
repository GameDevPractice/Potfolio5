#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "Character/CPlayerController.h"



void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.f;
	Direction = 0.f;
	Hight = 0.f;
	bOrient = false;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character == nullptr)
	{
		return;
	}
	
		Speed = Character->GetVelocity().Size2D();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		Hight = Character->GetVelocity().Z;
		ACPlayerController* PC = Cast<ACPlayerController>(Character->GetController());
		if (PC)
		{
			bOrient = PC->IsOrient();
		}

}

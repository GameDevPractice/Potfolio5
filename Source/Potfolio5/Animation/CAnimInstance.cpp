#include "CAnimInstance.h"
#include "GameFramework/Character.h"



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
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character == nullptr)
	{
		return;
	}
	
		Speed = Character->GetVelocity().Size2D();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		Hight = Character->GetVelocity().Z;
	

}

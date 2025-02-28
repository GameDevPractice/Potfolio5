#include "Actions/CAction_Jump.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UCAction_Jump::UCAction_Jump()
{
	ActionName = "Jump";
	
	
}

void UCAction_Jump::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if (CanAction(Instigator))
	{
		Character = Cast<ACharacter>(Instigator);
		if (Character == nullptr)
		{
			return;
		}
		if (Character->CanJump())
		{
			Character->Jump();
			Character->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCAction_Jump::StopJump, .7f,false);
			return;
		}
		
	}
	// Can not Jump
	StopAction_Implementation(Character);
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Cant Jump"));
}

void UCAction_Jump::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	
		Character = Cast<ACharacter>(Instigator);
		if (Character == nullptr)
		{
			return;
		}
		Character->StopJumping();
		Character->GetWorldTimerManager().ClearTimer(TimerHandle);
	
}

void UCAction_Jump::StopJump()
{
	StopAction_Implementation(Character);
}

#include "Actions/CAction_Jump.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CPlayer.h"

UCAction_Jump::UCAction_Jump()
{
	ActionName = "Jump";
	
	
}

void UCAction_Jump::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if (CanAction(Instigator))
	{
		ACPlayer* Player = Cast<ACPlayer>(Instigator);
		if (Player == nullptr)
		{
			return;
		}
		if (Player->CanJump())
		{
			Player->Jump();
			Player->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCAction_Jump::StopJump, 1.1f,false);
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
	
	ACPlayer* Player = Cast<ACPlayer>(Instigator);
	if (Player == nullptr)
	{
		return;
	}
	Player->StopJumping();
	Player->GetWorldTimerManager().ClearTimer(TimerHandle);
}

void UCAction_Jump::StopJump()
{
	StopAction_Implementation(Character);
}

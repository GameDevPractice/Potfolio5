#include "Actions/CAction_UnHand.h"
#include "GameFramework/Character.h"

UCAction_UnHand::UCAction_UnHand()
{
	ActionVaule = 0;
}

void UCAction_UnHand::StartAction_Implementation(AActor* Instigator)
{
	//Instigator´Â Controller
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (ActionVaule < ActionMontages.Num() && IsValid(ActionMontages[ActionVaule]))
	{
		Character->PlayAnimMontage(ActionMontages[ActionVaule]);
		ActionVaule++;
	}
	else
	{
		ActionVaule = 0;
	}
}

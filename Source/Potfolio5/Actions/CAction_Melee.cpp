#include "Actions/CAction_Melee.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"

UCAction_Melee::UCAction_Melee()
{
	ActionVaule = 0;
	bCombo = false;
	bSuccess = false;
}



void UCAction_Melee::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator); 
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (bCombo)
	{
		
		bSuccess = true;
		return;
	}
	if (!CanAction(Instigator))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "NotCan");
		//Super::StopAction_Implementation(Instigator);
		return;
	}
	//Instigator´Â Controller
	if ( IsValid(ActionMontages[ActionVaule]))
	{
		Character->PlayAnimMontage(ActionMontages[0]);
		bIsRunning = true;
	}
}

void UCAction_Melee::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	ActionVaule = 0;
	bIsRunning = false;
}

void UCAction_Melee::NextCombo(AActor* Instigator)
{
	if (!bSuccess && !CanAction(Instigator))
	{
		Super::StopAction_Implementation(Instigator);
		return;
	}
	bSuccess = false;
	
	ActionVaule++;
	ActionVaule = FMath::Clamp(ActionVaule, 0, ActionMontages.Num() - 1);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (IsValid(ActionMontages[ActionVaule]))
	{
		Character->PlayAnimMontage(ActionMontages[ActionVaule]);
	}
	return;
}

void UCAction_Melee::OnCombo()
{
	bCombo = true;
}

void UCAction_Melee::OffCombo()
{
	bCombo = false;
}

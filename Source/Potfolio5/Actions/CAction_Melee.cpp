#include "Actions/CAction_Melee.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"

UCAction_Melee::UCAction_Melee()
{
	ActionVaule = 0;
	bCombo = false;
	bSuccess = false;
	StopRate = 3.0f;
}



void UCAction_Melee::StartAction_Implementation(AActor* Instigator)
{
	
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	FTimerDelegate StopDelegate = FTimerDelegate::CreateUObject(this, &UCAction_Melee::StopAction_Implementation, Instigator);
	if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(StopTimer))
	{
		GetWorld(Instigator)->GetTimerManager().SetTimer(StopTimer, StopDelegate, StopRate, false);
	}
	if (bCombo)
	{
		bSuccess = true;
		return;
	}
	if (!CanAction(Instigator))
	{
		return;
	}
	//Instigator´Â Controller
	if ( IsValid(ActionMontages[0]))
	{
		GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);
		Character->PlayAnimMontage(ActionMontages[0]);
		bIsRunning = true;
	}
}

void UCAction_Melee::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	ActionVaule = 0;
	bIsRunning = false;
	GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, TEXT("StopAction"));
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

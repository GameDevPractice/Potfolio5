#include "Actions/CAction.h"

void UCAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running : %s"), *GetNameSafe(Instigator));

}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping : %s"), *GetNameSafe(this));
}

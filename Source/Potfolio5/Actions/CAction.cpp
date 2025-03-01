#include "Actions/CAction.h"
#include "Component/CActionComponent.h"


bool UCAction::CanAction_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, "Already Running");
		return false;
	}
	UCActionComponent* ActionComp = GetOwner();
	if (ActionComp->ActionTags.HasAny(BlockedTags))
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, "Have Block");
		return false;
	}
	return true;
}

void UCAction::StartAction_Implementation(AActor* Instigator)
{
	UCActionComponent* ActionComp = GetOwner();
	if (ActionComp == nullptr)
	{
		return;
	}
	ActionComp->ActionTags.AppendTags(GrantedTags);
}

void UCAction::StopAction_Implementation(AActor* Instigator)
{
	UCActionComponent* ActionComp = GetOwner();
	if (ActionComp == nullptr)
	{
		return;
	}
	ActionComp->ActionTags.RemoveTags(GrantedTags);
}



UWorld* UCAction::GetWorld(AActor* Actor)
{
	return Actor->GetWorld();
}

UCActionComponent* UCAction::GetOwner() const
{
	return Cast<UCActionComponent>(GetOuter());
}

#include "Animation/CNotifyState_Combo.h"
#include "CNotifyState_Combo.h"
#include "Character/CPlayer.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Actions/CAction_Melee.h"

FString UCNotifyState_Combo::GetNotifyName() const
{
	return "Combo";
}

void UCNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner != nullptr)
	{
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
		UCAction_Melee* MeleeAction = nullptr;
		TArray<UCAction_Melee*> MeleeActions = ActionComp->GetActionByClass(MeleeAction);
		if (MeleeActions.Num() <= 0)
		{
			return;
		}
		for (auto Melee : MeleeActions)
		{
			Melee->OnCombo();
		}
	}
	
}

void UCNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner != nullptr)
	{
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
		UCAction_Melee* MeleeAction = nullptr;
		TArray<UCAction_Melee*> MeleeActions = ActionComp->GetActionByClass(MeleeAction);
		if (MeleeActions.Num() <= 0)
		{
			return;
		}
		for (auto Melee : MeleeActions)
		{
			Melee->OffCombo();
		}
	}
}

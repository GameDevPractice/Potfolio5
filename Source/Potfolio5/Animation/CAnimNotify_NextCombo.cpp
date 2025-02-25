#include "Animation/CAnimNotify_NextCombo.h"
#include "CAnimNotify_NextCombo.h"
#include "Character/CPlayer.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Actions/CAction_Melee.h"

FString UCAnimNotify_NextCombo::GetNotifyName() const
{
	return "NextCombo";
}

void UCAnimNotify_NextCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCAction_Melee* MeleeAction = nullptr;
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner != nullptr)
	{
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
		
		TArray<UCAction_Melee*> MeleeActions = ActionComp->GetActionByClass(MeleeAction);
		if (MeleeActions.Num() <= 0)
		{
			return;
		}
		for (auto Melee : MeleeActions)
		{
			Melee->NextCombo(Owner);
		}
		return;
	}
}

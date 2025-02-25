#include "Animation/CAnimNotify_EndAction.h"
#include "CAnimNotify_EndAction.h"
#include "Character/CPlayer.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Actions/CAction_Melee.h"

FString UCAnimNotify_EndAction::GetNotifyName() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCAction_Melee* MeleeAction = nullptr;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("EndAction"));
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner != nullptr)
	{
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
		ActionClass = ActionComp->GetActionByClass(MeleeAction);
		if (ActionClass.Num() > 0)
		{
			for (auto Action : ActionClass)
			{
				Action->StopAction(Owner);
			}
		}
	}
}

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
		if (ActionComp)
		{
			for (UCAction* Action : ActionComp->GetActions())
			{
				if (Action && Action->IsRunning()) // 실행 중인 액션만 확인
				{
					UCAction_Melee* MeleeAction = Cast<UCAction_Melee>(Action);
					if (MeleeAction)
					{
						MeleeAction->OnCombo();  // 실행 중인 액션에 대해서만 콤보 실행
					}
				}
			}
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
		if (ActionComp)
		{
			for (UCAction* Action : ActionComp->GetActions())
			{
				if (Action && Action->IsRunning()) // 실행 중인 액션만 확인
				{
					UCAction_Melee* MeleeAction = Cast<UCAction_Melee>(Action);
					if (MeleeAction)
					{
						MeleeAction->OffCombo();  // 실행 중인 액션에 대해서만 콤보 실행
					}
				}
			}
		}
	}
}

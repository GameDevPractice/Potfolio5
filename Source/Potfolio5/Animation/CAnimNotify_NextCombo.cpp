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
                        MeleeAction->NextCombo(Owner);  // 실행 중인 액션에 대해서만 콤보 실행
                    }
                }
            }
        }
    }
}

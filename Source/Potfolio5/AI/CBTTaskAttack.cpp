#include "AI/CBTTaskAttack.h"
#include "CBTTaskAttack.h"
#include "Component/CActionComponent.h"
#include "AI/CAIController.h"

UCBTTaskAttack::UCBTTaskAttack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UCBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* Panwn = AIC->GetPawn();
	if (Panwn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is nullptr in UCBTTaskAttack::ExecuteTask"));
		return EBTNodeResult::Failed;
	}
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Panwn->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ActionComp is nullptr in UCBTTaskAttack::ExecuteTask"));
		return EBTNodeResult::Failed;
	}
	if (ActionComp->StartActionByName(Panwn, AttackName))
	{
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

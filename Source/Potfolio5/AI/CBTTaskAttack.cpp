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
		return EBTNodeResult::Failed;
	}
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Panwn->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	if (ActionComp->StartActionByName(Panwn, "Attack"))
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

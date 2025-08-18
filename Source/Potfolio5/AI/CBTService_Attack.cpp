#include "AI/CBTService_Attack.h"
#include "AI/CAIController.h"
#include "Component/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTService_Attack::UCBTService_Attack()
{
	NodeName = TEXT("Attack Service");
}

void UCBTService_Attack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AIC = Cast<ACAIController>(OwnerComp.GetAIOwner());
	if (AIC == nullptr)
	{
		return;
	}
	BehaviorComp = AIC->GetBehaviorComp();
	if (BehaviorComp == nullptr)
	{
		return;
	}

	if (AIC->GetBlackboardComponent()->GetValueAsBool("AttackingKey"))
	{
		return;
	}

	BehaviorComp->SetOnAttackMode();
	float RandomValue = FMath::FRand();
	if (RandomValue <0.7f)
	{
		BehaviorComp->SetNomalMode();
		
	}
	else if ( 0.7f < RandomValue &&RandomValue < 0.9f)
	{
		BehaviorComp->SetHeavyMode();
	}
	else
	{
		BehaviorComp->SetSpecialMode();
	}
}

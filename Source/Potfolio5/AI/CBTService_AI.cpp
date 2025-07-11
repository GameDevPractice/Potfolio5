#include "AI/CBTService_AI.h"
#include "AI/CAIController.h"
#include "Component/CBehaviorComponent.h"
#include "Character/CPlayer.h"


UCBTService_AI::UCBTService_AI()
{
	NodeName = TEXT("AI Service");
}

void UCBTService_AI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetAIOwner());
	FRotator PawnRot = AIC->GetPawn()->GetActorRotation();
	AIC->SetControlRotation(PawnRot);
	if (AIC == nullptr)
	{
		
		return;
	}
	UCBehaviorComponent* BehaviorComp = AIC->GetBehaviorComp();
	if (BehaviorComp == nullptr)
	{
		return;
	}
	
	ACPlayer* Player = BehaviorComp->GetPlayer();
	if (Player == nullptr)
	{
		BehaviorComp->SetWaitMode();
		return;
	}
	else
	{
		float Distance = AIC->GetPawn()->GetDistanceTo(Player);

		if (Distance > AIC->GetBehaviorRange())
		{
			AIC->SetFocus(Player);			
			BehaviorComp->SetApprochMode();
		}
		else if (Distance < AIC->GetBehaviorRange())
		{
			AIC->SetFocus(Player);
			BehaviorComp->SetAttackMode();
		}
		return;
	}

}


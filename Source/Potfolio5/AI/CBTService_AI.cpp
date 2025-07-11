#include "AI/CBTService_AI.h"
#include "AI/CAIController.h"
#include "Component/CBehaviorComponent.h"
#include "Component/CAttributeComponent.h"
#include "Character/CPlayer.h"
#include "Character/CEnemy.h"


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

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	if (AIC == nullptr)
	{
		
		return;
	}
	UCAttributeComponent* AttributeComp = Cast<UCAttributeComponent>(Enemy->GetComponentByClass(UCAttributeComponent::StaticClass()));
	if (AttributeComp == nullptr)
	{
		return;
	}
	if (AttributeComp->GetHealth() <= 0.f)
	{
		AIC->GetBehaviorComp()->SetDeadMode();
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
		float Distance = Enemy->GetDistanceTo(Player);

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


#include "AI/CAIController.h"
#include "CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/CEnemy.h"
#include "Character/CPlayer.h"
#include "Component/CBehaviorComponent.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	BehaviorRange = 1000.f;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	BehaviorComp = CreateDefaultSubobject<UCBehaviorComponent>(TEXT("BehaviorComp"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	Sight->SightRadius = 2000.f;
	Sight->LoseSightRadius = 2500.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BlackboardComp = Blackboard;
	OwnerEnemy = Cast<ACEnemy>(InPawn);
	ensure(OwnerEnemy->GetBehaviorTree());
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, BlackboardComp);
	ensure(BlackboardComp);
	BehaviorComp->SetBlackBoard(BlackboardComp);
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnUnPossess()
{
	PerceptionComp->OnPerceptionUpdated.Clear();
}

void ACAIController::Tick(float DeltaTime)
{
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	ACPlayer* Player = nullptr;
	for (const auto& Actor : PerceivedActors)
	{
		Player = Cast<ACPlayer>(Actor);

		if (Player)
		{
			break;
		}
	}
	
	BlackboardComp->SetValueAsObject("Playerkey", Player);
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

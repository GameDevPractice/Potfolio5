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
	BehaviorRange = 1000.f;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	BehaviorComp = CreateDefaultSubobject<UCBehaviorComponent>(TEXT("BehaviorComp"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
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
	OwnerEnemy = Cast<ACEnemy>(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, BlackboardComp);
	if (BehaviorComp != nullptr)
	{
		this->Blackboard = BlackboardComp;
		BehaviorComp->SetBlackBoard(Blackboard);
	}
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
	
	Blackboard->SetValueAsObject("Playerkey", Player);
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

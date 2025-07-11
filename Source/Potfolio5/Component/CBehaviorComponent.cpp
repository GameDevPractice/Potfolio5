#include "Component/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CPlayer.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	PlayerKey = "Playerkey";
	BehaviorTypeKey = "BehaviorKey";
}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBehaviorComponent::SetBlackBoard(UBlackboardComponent* InBlackBoardComp)
{
	BlackboardComp = InBlackBoardComp;
}

ACPlayer* UCBehaviorComponent::GetPlayer()
{
	return Cast<ACPlayer>(BlackboardComp->GetValueAsObject(PlayerKey));
}

void UCBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCBehaviorComponent::SetHitMode()
{
	SetBehaviorType(EBehaviorType::Hit);
}

void UCBehaviorComponent::SetWaitMode()
{
	SetBehaviorType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetAttackMode()
{
	SetBehaviorType(EBehaviorType::Attack);
}

void UCBehaviorComponent::SetMoveMode()
{
	SetBehaviorType(EBehaviorType::Move);
}

void UCBehaviorComponent::SetApprochMode()
{
	SetBehaviorType(EBehaviorType::Approch);
}

void UCBehaviorComponent::SetBehaviorType(EBehaviorType Type)
{
	BlackboardComp->SetValueAsEnum(BehaviorTypeKey, (uint8)Type);
}


#include "Component/CBehaviorComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBehaviorComponent::SetBlackBoard(UBlackboardComponent* InBlackBoardComp)
{
	if (InBlackBoardComp == nullptr)
	{
		return;
	}
	BlackboardComp = InBlackBoardComp;
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

void UCBehaviorComponent::SetBehaviorType(EBehaviorType Type)
{
	if (BehaviorType != Type)
	{
		BehaviorType = Type;
	}
}


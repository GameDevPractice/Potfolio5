#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Attack.generated.h"

class UCBehaviorComponent;
class ACAIController;

UCLASS()
class POTFOLIO5_API UCBTService_Attack : public UBTService
{
	GENERATED_BODY()
	
	UCBTService_Attack();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UCBehaviorComponent* BehaviorComp;
	ACAIController* AIC;

private:
	bool bIsAttacking = false;

};

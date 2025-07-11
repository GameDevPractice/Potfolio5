#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_AI.generated.h"

UCLASS()
class POTFOLIO5_API UCBTService_AI : public UBTService
{
	GENERATED_BODY()
	UCBTService_AI();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};

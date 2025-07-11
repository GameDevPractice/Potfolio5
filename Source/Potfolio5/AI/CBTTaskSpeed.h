#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskSpeed.generated.h"

UCLASS()
class POTFOLIO5_API UCBTTaskSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskSpeed();
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category = "speed")
	float Speed;
};

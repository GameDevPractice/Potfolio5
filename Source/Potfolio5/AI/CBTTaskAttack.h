#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskAttack.generated.h"

UCLASS()
class POTFOLIO5_API UCBTTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskAttack();
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	FName AttackName;

};

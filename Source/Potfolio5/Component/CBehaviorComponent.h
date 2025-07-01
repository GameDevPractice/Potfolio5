#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Hit,Wait,Attack,Move,Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTFOLIO5_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetBlackBoard(UBlackboardComponent* InBlackBoardComp);

public:
	void SetHitMode();
	void SetWaitMode();
	void SetAttackMode();
	void SetMoveMode();

private:
	void SetBehaviorType(EBehaviorType Type);

private:
	EBehaviorType BehaviorType;

private:
	UBlackboardComponent* BlackboardComp;
		
};

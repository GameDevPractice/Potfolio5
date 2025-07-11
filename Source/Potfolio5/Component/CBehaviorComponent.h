#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;
class ACPlayer;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Hit,Wait,Attack,Move,Approch,Dead,Max
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

	ACPlayer* GetPlayer();

public:
	UFUNCTION(BlueprintCallable)
	void SetHitMode();
	UFUNCTION(BlueprintCallable)
	void SetWaitMode();
	UFUNCTION(BlueprintCallable)
	void SetAttackMode();
	UFUNCTION(BlueprintCallable)
	void SetMoveMode();

	UFUNCTION(BlueprintCallable)
	void SetApprochMode();
	UFUNCTION(BlueprintCallable)
	void SetDeadMode();

private:
	void SetBehaviorType(EBehaviorType Type);

private:
	EBehaviorType BehaviorType;

private:
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName PlayerKey ;
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName BehaviorTypeKey;
		
};

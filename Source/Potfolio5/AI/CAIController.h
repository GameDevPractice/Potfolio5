#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class ACEnemy;
class UCBehaviorComponent;

UCLASS()
class POTFOLIO5_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);


public:
	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }
	UCBehaviorComponent* GetBehaviorComp() { return BehaviorComp; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly)
	UCBehaviorComponent* BehaviorComp;

private:
	UPROPERTY(EditAnywhere)
	float BehaviorRange;

private:
	ACEnemy* OwnerEnemy;

	UPROPERTY(EditAnywhere)
	UAISenseConfig_Sight* Sight;
};

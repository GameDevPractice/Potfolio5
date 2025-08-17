#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

class UCActionComponent;
class UCAttributeComponent;
class ACAIController;
class UCMontageComponent;
class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyBeginOverlap, UPrimitiveComponent*, OverlappedComp, const FHitResult&, SweepResult);

UCLASS()
class POTFOLIO5_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	//Check Boos
	UFUNCTION(BlueprintCallable, Category = "Attack")
	FORCEINLINE bool IsBoos() const { return bBoos; }

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return Capsule; }


protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

protected:
	USkeletalMesh* Mesh;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly)
	UCapsuleComponent* Capsule;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCMontageComponent* MontageComp;

protected:
	bool bBoos;

public:
	UPROPERTY()
	FOnEnemyBeginOverlap OnBeginOverlap;

private:
	ACAIController* AIC;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};

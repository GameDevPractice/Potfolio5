#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoosReward.generated.h"

class UBoxComponent;

UCLASS()
class POTFOLIO5_API ACBoosReward : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoosReward();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetMesh(USkeletalMesh* NewMesh);

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* Mesh;
};

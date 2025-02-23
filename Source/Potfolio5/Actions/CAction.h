#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

UCLASS(Blueprintable)
class POTFOLIO5_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	virtual void AddActionMontage(UAnimMontage* Montage) {};
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;	

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TArray<UAnimMontage*> ActionMontages;

};

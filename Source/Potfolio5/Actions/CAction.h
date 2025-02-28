#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CAction.generated.h"

class UCActionComponent;

UCLASS(Blueprintable)
class POTFOLIO5_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	 void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	 void StopAction(AActor* Instigator);

	virtual void AddActionMontage(UAnimMontage* Montage) {};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	bool CanAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const { return bIsRunning; }

	UWorld* GetWorld(AActor* Actor);

protected:
	UFUNCTION(BlueprintCallable, Category = "Action")
	UCActionComponent* GetOwner() const;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;	

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TArray<UAnimMontage*> ActionMontages;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameplayTag")
	FGameplayTagContainer GrantedTags;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameplayTag")
	FGameplayTagContainer BlockedTags;

	bool bIsRunning = false;

};

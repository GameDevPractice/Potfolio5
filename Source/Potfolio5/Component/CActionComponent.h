#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CActionComponent.generated.h"

class UCAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTFOLIO5_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(TSubclassOf<UCAction> ActionClass);

	//이름으로 찾게 되는데 이를 확인하기 위해 Bool
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator,FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	TArray<UCAction*> GetActions() const { return Actions; }

	template<typename T>
	TArray<T*> GetActionByClass(T* FindAction)
	{
		TArray<T*> Result;
		for (auto Action : Actions)
		{
			if (T* CastedAction = Cast<T>(Action)) // 타입 캐스팅
			{
				Result.Add(CastedAction);
				
			}
		}
		return Result;
	}

protected:
	TArray<UCAction*> Actions;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Action")
	TArray<TSubclassOf<UCAction>> AddActions;


public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameplayTag")
	FGameplayTagContainer ActionTags;
		
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMontageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTFOLIO5_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void PlayunEquip();
	UFUNCTION(BlueprintCallable)
	void PlayHit();
	UFUNCTION(BlueprintCallable)
	void PlayHitReact();
	UFUNCTION(BlueprintCallable)
	void PlayGetOn();


	UFUNCTION(BlueprintCallable)
	float GetHitRate() { return HitMontage->RateScale; }
	UFUNCTION(BlueprintCallable)
	float GetHitReactRate() { return HitReactMontage->RateScale; }
	UFUNCTION(BlueprintCallable)
	float GetGetOntRate() { return GetOnMontage->RateScale; }

private:
	void PlayMontage(UAnimMontage* Montage);

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* GetOnMontage;
		
};

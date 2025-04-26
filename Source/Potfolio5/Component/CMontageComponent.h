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

private:
	void PlayMontage(UAnimMontage* Montage);

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* HitMontage;
		
};

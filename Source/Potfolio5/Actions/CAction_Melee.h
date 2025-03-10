#pragma once

#include "CoreMinimal.h"
#include "Actions/CAction.h"
#include "CAction_Melee.generated.h"

UCLASS()
class POTFOLIO5_API UCAction_Melee : public UCAction
{
	GENERATED_BODY()
public:
	UCAction_Melee();
	
public:
	void NextCombo(AActor* Instigator);

	void OnCombo();
	void OffCombo();

private:
	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 ActionVaule;

	bool bCombo;
	bool bSuccess;

	UPROPERTY(EditDefaultsOnly)
	float StopRate;

	FTimerHandle StopTimer;
};

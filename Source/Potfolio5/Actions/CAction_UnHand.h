#pragma once

#include "CoreMinimal.h"
#include "Actions/CAction.h"
#include "CAction_UnHand.generated.h"

UCLASS()
class POTFOLIO5_API UCAction_UnHand : public UCAction
{
	GENERATED_BODY()
public:
	UCAction_UnHand();
	
private:
	void StartAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 ActionVaule;

};

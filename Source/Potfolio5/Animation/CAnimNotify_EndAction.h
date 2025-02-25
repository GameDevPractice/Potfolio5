#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndAction.generated.h"

class UCAction_Melee;

UCLASS()
class POTFOLIO5_API UCAnimNotify_EndAction : public UAnimNotify
{
	GENERATED_BODY()

protected:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UCAction_Melee*> ActionClass;
};

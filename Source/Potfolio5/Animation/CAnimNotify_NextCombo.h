#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_NextCombo.generated.h"

UCLASS()
class POTFOLIO5_API UCAnimNotify_NextCombo : public UAnimNotify
{
	GENERATED_BODY()
	
	protected:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

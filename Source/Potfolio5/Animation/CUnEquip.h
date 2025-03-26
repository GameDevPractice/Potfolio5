#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CUnEquip.generated.h"

UCLASS()
class POTFOLIO5_API UCUnEquip : public UAnimNotify
{
	GENERATED_BODY()
protected:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNotifyState_Combo.generated.h"

UCLASS()
class POTFOLIO5_API UCNotifyState_Combo : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	FString GetNotifyName() const;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CAction.h"
#include "CAction_Jump.generated.h"

UCLASS()
class POTFOLIO5_API UCAction_Jump : public UCAction
{
	GENERATED_BODY()

public:
	UCAction_Jump();

	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	
protected:
	void StopJump();

protected:
	FTimerHandle TimerHandle;
	ACharacter* Character;

};

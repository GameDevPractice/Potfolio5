#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayer;

UCLASS()
class POTFOLIO5_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void SetupInputComponent();

	UFUNCTION(BlueprintCallable)
	void AddCharacter(ACPlayer* InCharacter);

private:
	void ChangeCharacter1();
	void ChangeCharacter2();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Character")
	TArray<AActor*> CharacterArray;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayer;
class UUserWidget;

UCLASS()
class POTFOLIO5_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	TArray<ACPlayer*> GetPlayer() const { return Characters; }
protected:
	virtual void SetupInputComponent();

	UFUNCTION(BlueprintCallable)
	void AddCharacter(ACPlayer* InCharacter);

private:
	void ChangeCharacter1();
	void ChangeCharacter2();

protected:
	TArray<AActor*> CharacterArray;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Character")
	TArray<ACPlayer*> Characters;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	UUserWidget* Widget;
};

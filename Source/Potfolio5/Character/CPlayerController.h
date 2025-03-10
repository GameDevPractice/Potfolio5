#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayer;
class UUserWidget;
class UNiagaraSystem;

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

	UFUNCTION(BlueprintCallable)
	float GetRate() const { return ChangeTime; }

	UFUNCTION(BlueprintCallable)
	int32 GetInt() const { return CharacterInt; }

	UFUNCTION(BlueprintCallable)
	void ChangeCharacterAction(ACPlayer* InAction, int32 NewInt);
protected:
	virtual void SetupInputComponent();

	UFUNCTION(BlueprintCallable)
	void AddCharacter(ACPlayer* InCharacter);

private:
	void ChangeCharacter1();
	void ChangeCharacter2();

	void ChangeCharactr(int32 NewInt);

	void OnCanChange();

protected:
	TArray<AActor*> CharacterArray;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Character")
	TArray<ACPlayer*> Characters;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	UUserWidget* Widget;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
	UNiagaraSystem* ChangeEffect;

	bool bCanChange; //교체가능 여부
	UPROPERTY(EditDefaultsOnly, Category = "Change")
	float ChangeTime;

	int32 CharacterInt;
};

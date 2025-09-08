#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayer;
class UUserWidget;
class UNiagaraSystem;
class UWB_Player_Change;

UCLASS()
class POTFOLIO5_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetPlayer() const { return Characters; }

	UFUNCTION(BlueprintCallable)
	float GetRate() const { return ChangeTime; }

	UFUNCTION(BlueprintCallable)
	int32 GetInt() const { return CharacterInt; }

	UFUNCTION(BlueprintCallable)
	void ChangeCharacterAction(ACPlayer* InAction, int32 NewInt);
protected:
	virtual void SetupInputComponent();

public:
	UFUNCTION(BlueprintCallable)
	void AddCharacter(AActor* InCharacter);

private:
	void ChangeCharacter1();
	void ChangeCharacter2();

	void ChangeCharacter3();

	void ChangeCharactr(int32 NewInt);

	void OnCanChange();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Character")
	TArray<AActor*> Characters;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	UUserWidget* Widget;
	UWB_Player_Change* ChagneWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
	UNiagaraSystem* ChangeEffect;

	bool bCanChange; //교체가능 여부
	UPROPERTY(EditDefaultsOnly, Category = "Change")
	float ChangeTime;

	int32 CharacterInt;

};

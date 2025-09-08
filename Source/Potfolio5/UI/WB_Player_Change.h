#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WB_Player_Change.generated.h"

UCLASS()
class POTFOLIO5_API UWB_Player_Change : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ChangeCharacter(int32 NewInt);

	UFUNCTION(BlueprintNativeEvent)
	void AddCharacter(AActor* InCharacter);
};

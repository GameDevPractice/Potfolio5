#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS()
class POTFOLIO5_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ChangeCharacter(int32 NewInt);
};

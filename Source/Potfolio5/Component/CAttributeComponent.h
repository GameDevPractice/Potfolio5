#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTFOLIO5_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	float DamageHealth(float DamageAmount, AActor* DamagedActor, AActor* Instigator, AController* InInstigatorController);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHealth() const { return MaxHealth; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float Stamina;


		
};

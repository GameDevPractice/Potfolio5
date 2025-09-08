#include "Component/CAttributeComponent.h"
#include "Component/CActionComponent.h"
#include "Engine/DamageEvents.h"
#include "Character/CPlayerController.h"

UCAttributeComponent::UCAttributeComponent()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
	Stamina = 100.f;
}


// Called when the game starts
void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

float UCAttributeComponent::DamageHealth(float DamageAmount, AActor* DamagedActor, AActor* Instigator, AController* InInstigatorController)
{
	UCActionComponent* ActionComp = Cast<UCActionComponent>(DamagedActor->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		return 0.f;
	}
	//TakeDamage
	if (DamageAmount <= 0.f)
	{
		return 0.f;
	}
	FDamageEvent DamageEvent;
	float realDamage = DamagedActor->TakeDamage(DamageAmount, DamageEvent, InInstigatorController, nullptr);
	Health -= realDamage;
	if (Health <= 0.f)
	{
		//Death logic
		
		ActionComp->StartActionByName(DamagedActor, "Death");
		return 0.f;
	}
	else
	{
		//Action Start -> Attacker is Instigator
		ActionComp->StartActionByName(Instigator, "Hit");
	}
	return realDamage;
}



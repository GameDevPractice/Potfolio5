#include "Component/CAttributeComponent.h"
#include "Engine/DamageEvents.h"

UCAttributeComponent::UCAttributeComponent()
{
	Health = 100.f;
	Stamina = 100.f;
}


// Called when the game starts
void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

float UCAttributeComponent::DamageHealth(float DamageAmount, AActor* DamagedActor)
{
	//TakeDamage
	if (DamageAmount <= 0.f)
	{
		return 0.f;
	}
	FDamageEvent DamageEvent;
	float realDamage = DamagedActor->TakeDamage(DamageAmount, DamageEvent,GetOwner()->GetInstigatorController(), GetOwner());
	Health -= realDamage;
	if (Health <= 0.f)
	{
		//Death logic
		return 0.f;
	}
	return realDamage;
}



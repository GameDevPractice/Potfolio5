#include "Component/CMontageComponent.h"
#include "CMontageComponent.h"
#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent()
{

}


void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCMontageComponent::PlayunEquip()
{
	PlayMontage(UnEquipMontage);
}

void UCMontageComponent::PlayHit()
{
	PlayMontage(HitMontage);
}

void UCMontageComponent::PlayHitReact()
{
	PlayMontage(HitReactMontage);
}

void UCMontageComponent::PlayGetOn()
{
	PlayMontage(GetOnMontage);
}

void UCMontageComponent::PlayMontage(UAnimMontage* Montage)
{
	if (Montage == nullptr)
	{
		return;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}
	Character->PlayAnimMontage(Montage);
	
}



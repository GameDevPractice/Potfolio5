#include "Actions/CAction_Melee.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "Character/CPlayer.h"
#include "Kismet/GameplayStatics.h"

UCAction_Melee::UCAction_Melee()
{
	ActionVaule = 0;
	bCombo = false;
	bSuccess = false;
	StopRate = 1.0f;
	Damage = 10.f;
}



void UCAction_Melee::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACPlayer* Player = Cast<ACPlayer>(Instigator);
	//Check Binded and Bind
	if (!Player->OnBeginOverlap.IsBound())
	{
	Player->OnBeginOverlap.AddDynamic(this, &UCAction_Melee::MeleeOverlap);
	}
	ACharacter* Character = Cast<ACharacter>(Instigator);
	FTimerDelegate StopDelegate = FTimerDelegate::CreateUObject(this, &UCAction_Melee::StopAction_Implementation, Instigator);
	if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(StopTimer))
	{
		GetWorld(Instigator)->GetTimerManager().SetTimer(StopTimer, StopDelegate, StopRate, false);
	}
	if (GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
	{
		GetWorld(Instigator)->GetTimerManager().ClearTimer(AuraTimer);
	}
	if (bCombo)
	{
		bSuccess = true;
		return;
	}
	if (!CanAction(Instigator))
	{
		return;
	}
	//Instigator´Â Controller
	if ( IsValid(ActionMontages[0]))
	{
		Character->PlayAnimMontage(ActionMontages[0]);
		bIsRunning = true;
		if (Player != nullptr)
		{
			Player->SetActorRotation(FRotator(0, Player->GetControlRotation().Yaw, 0));
			Player->PlayEquip();
		}
	}
}

void UCAction_Melee::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	ActionVaule = 0;
	bIsRunning = false;
	bCombo = false;
	if (GetWorld(Instigator)->GetTimerManager().IsTimerActive(StopTimer))
	{
		GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);
	}
	
	FTimerDelegate UnEquipDelegate = FTimerDelegate::CreateUObject(this, &UCAction_Melee::PlayUnEquip, Instigator);
	if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
	{
		GetWorld(Instigator)->GetTimerManager().SetTimer(AuraTimer, UnEquipDelegate, 10.0f, false);
	}
	ACPlayer* Player = Cast<ACPlayer>(Instigator);
	Player->OnBeginOverlap.Clear();
	
}

void UCAction_Melee::PlayUnEquip(AActor* Instigator)
{
	ACPlayer* Player = Cast<ACPlayer>(Instigator);
	if (Player != nullptr && Player->IsEquip())
	{
		if (!bIsRunning)
		{
		Player->PlayUnEquip();
		}
	}
	if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
	{
		GetWorld(Instigator)->GetTimerManager().ClearTimer(AuraTimer);
	}
}

void UCAction_Melee::MeleeOverlap(UPrimitiveComponent* OverlappedComp, const FHitResult& SweepResult)
{
	//Check OtherActor
	AActor* OtherActor = SweepResult.GetActor();
	if (OtherActor == nullptr)
	{
		return;
	}

	//Check AttributeComponent and Apply Damage
	UCAttributeComponent* AttributeComp = Cast<UCAttributeComponent>(OtherActor->GetComponentByClass(UCAttributeComponent::StaticClass()));
	if (AttributeComp == nullptr)
	{
		return;
	}
	AttributeComp->DamageHealth(Damage, OtherActor, GetOwner()->GetOwner(), GetOwner()->GetOwner()->GetInstigatorController());
}

void UCAction_Melee::NextCombo(AActor* Instigator)
{
	if (!bSuccess )
	{
		return;
	}
	bSuccess = false;
	GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);
	ActionVaule++;
	ActionVaule = FMath::Clamp(ActionVaule, 0, ActionMontages.Num() - 1);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (IsValid(ActionMontages[ActionVaule]))
	{
		Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw, 0));
		Character->PlayAnimMontage(ActionMontages[ActionVaule]);
	}
	return;
}

void UCAction_Melee::OnCombo()
{
	bCombo = true;
}

void UCAction_Melee::OffCombo()
{
	bCombo = false;
}

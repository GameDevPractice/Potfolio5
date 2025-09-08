#include "Character/CPlayerController.h"
#include "GameFramework/Character.h"
#include "Character/CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "UI/WB_Player_Change.h"
#include "Component/CActionComponent.h"


ACPlayerController::ACPlayerController()
{
	ChangeTime = 5.0f;
	bCanChange = true;
	CharacterInt = 0;
}

void ACPlayerController::BeginPlay()
{
	Characters[0] = Cast<ACPlayer>(GetPawn());
	if (WidgetClass)
	{
	Widget = CreateWidget(this, WidgetClass);
	}

	if (Widget != nullptr)
	{
		ChagneWidget = Cast<UWB_Player_Change>(Widget);
		if (ChagneWidget == nullptr)
		{
			return;
		}
		ChagneWidget->AddToViewport();
		ChagneWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACPlayerController::ChangeCharacterAction(ACPlayer* InAction, int32 NewInt)
{
	// 교체 시간 
	FTimerHandle ChangeHandle;
	GetWorldTimerManager().SetTimer(ChangeHandle, this, &ACPlayerController::OnCanChange, ChangeTime, false);
	bCanChange = false;

	//교체 기능
	FVector Location = Characters[NewInt]->GetActorLocation();
	FRotator Rotation = Characters[NewInt]->GetActorRotation();
	Characters[NewInt]->SetActorLocation(GetPawn()->GetActorLocation());
	Characters[NewInt]->SetActorRotation(GetPawn()->GetActorRotation());

	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	OnPossess(Cast<ACPlayer>(Characters[NewInt]));
	InAction->SetActorLocation(Location);
	InAction->SetActorRotation(Rotation);
	// 회전 복원
	SetControlRotation(CameraRotation);
	ChagneWidget->ChangeCharacter(NewInt);
	if (ChangeEffect == nullptr)
	{
		return;
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ChangeEffect, GetPawn()->GetActorLocation() - FVector(0.0f,0.0f,80.f) );
	
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Change1", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter1);
	InputComponent->BindAction("Change2", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter2);
	InputComponent->BindAction("Change3", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter3);
}

void ACPlayerController::AddCharacter(AActor* InCharacter)
{
	ChagneWidget->AddCharacter(InCharacter);
}

void ACPlayerController::ChangeCharacter1()
{
	if (ensure(Characters[0] != nullptr) && Characters[0] != Cast<ACPlayer>(GetPawn()))
	{
		ChangeCharactr(0);
	}
}

void ACPlayerController::ChangeCharacter2()
{
	if ((Characters.Num() < 2))
	{
		return;
	}
	if (ensure(Characters[1] != nullptr) && Characters[1] != Cast<ACPlayer>(GetPawn()))
	{
		ChangeCharactr(1);
	}
}

void ACPlayerController::ChangeCharacter3()
{
	if ((Characters.Num() < 3))
	{
		return;
	}
	if (ensure(Characters[2] != nullptr) && Characters[2] != Cast<ACPlayer>(GetPawn()))
	{
		ChangeCharactr(2);
	}
}

void ACPlayerController::ChangeCharactr(int32 NewInt)
{
	CharacterInt = NewInt;
	ACPlayer* Temp = Cast<ACPlayer>(GetPawn());
	//교체 가능 판단
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Temp->GetComponentByClass(UCActionComponent::StaticClass()));
	 if (ActionComp == nullptr)
	 {
		 return;
	 }
	if (bCanChange == false)
	{
		return;
	}
	if (!ActionComp->StartActionByName(Temp, "Change"))
	{
		return;
	}
	if (!ActionComp->StopActionByName(Temp, "Change"))
	{
		return;
	}
}


void ACPlayerController::OnCanChange()
{
	bCanChange = true;
}
	


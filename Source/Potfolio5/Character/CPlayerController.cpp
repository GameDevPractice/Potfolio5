#include "Character/CPlayerController.h"
#include "GameFramework/Character.h"
#include "Character/CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "UI/MyUserWidget.h"
#include "Component/CActionComponent.h"


ACPlayerController::ACPlayerController()
{
	ChangeTime = 5.0f;
	bCanChange = true;
}

void ACPlayerController::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPlayer::StaticClass(), CharacterArray);
	if (CharacterArray.Num() > 0)
	{
		for (auto NewCharacter : CharacterArray)
		{
			Characters.Add(Cast<ACPlayer>(NewCharacter));
		}
		Characters[0] = Cast<ACPlayer>(GetPawn());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Character"));
	}
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Controller Begin Play"));

	if (WidgetClass)
	{
	Widget = CreateWidget(this, WidgetClass);
	}

	if (Widget != nullptr)
	{
		Widget->AddToViewport();
	}
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Change1", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter1);
	InputComponent->BindAction("Change2", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter2);
}

void ACPlayerController::AddCharacter(ACPlayer* InCharacter)
{
	Characters.Add(InCharacter);
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
	if (ensure(Characters[1] != nullptr) && Characters[1] != Cast<ACPlayer>(GetPawn()))
	{
		ChangeCharactr(1);
	}
}

void ACPlayerController::ChangeCharactr(int32 NewInt)
{
	ACPlayer* Temp = Cast<ACPlayer>(GetPawn());
	//교체 가능 판단
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Temp->GetComponentByClass(UCActionComponent::StaticClass()));
	 if (ensure(ActionComp == nullptr))
	 {
		 return;
	 }
	if (bCanChange == false)
	{
		return;
	}
	if (ActionComp->ActionTags.IsEmpty() == false)
	{
		return;
	}
	// 교체 시간 
	FTimerHandle ChangeHandle;
	GetWorldTimerManager().SetTimer(ChangeHandle, this, &ACPlayerController::OnCanChange, ChangeTime, false);
	bCanChange = false;

	//교체 기능
	FVector Location = Characters[NewInt]->GetActorLocation();
	FRotator Rotation = Characters[NewInt]->GetActorRotation();
	Characters[NewInt]->SetActorLocation(GetPawn()->GetActorLocation());
	Characters[NewInt]->SetActorRotation(GetPawn()->GetActorRotation());
	Possess(Cast<ACPlayer>(Characters[NewInt]));
	Temp->SetActorLocation(Location);
	Temp->SetActorRotation(Rotation);
	if (ChangeEffect == nullptr)
	{
		return;
	}
	if (UMyUserWidget* ChagneWidget = Cast<UMyUserWidget>(Widget))
	{
		ChagneWidget->ChangeCharacter(NewInt);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ChangeEffect, GetPawn()->GetActorLocation() - FVector(0.0f, 0.0f, 150.f));
	}
}


void ACPlayerController::OnCanChange()
{
	bCanChange = true;
}
	


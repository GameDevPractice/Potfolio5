#include "Character/CPlayerController.h"
#include "GameFramework/Character.h"
#include "Character/CPlayer.h"
#include "Kismet/GameplayStatics.h"

ACPlayerController::ACPlayerController()
{
	
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
		ACPlayer* Temp = Cast<ACPlayer>(GetPawn());
		FVector Location = Characters[0]->GetActorLocation();
		FRotator Rotation = Characters[0]->GetActorRotation();
		Characters[0]->SetActorLocation(GetPawn()->GetActorLocation());
		Characters[0]->SetActorRotation(GetPawn()->GetActorRotation());
		Possess(Cast<ACPlayer>(Characters[0]));
		Temp->SetActorLocation(Location);
		Temp->SetActorRotation(Rotation);
	}
	UE_LOG(LogTemp, Warning, TEXT("Change %s"), *GetNameSafe(Characters[0]));
}

void ACPlayerController::ChangeCharacter2()
{
	if (ensure(Characters[1] != nullptr) && Characters[1] != Cast<ACPlayer>(GetPawn()))
	{
		ACPlayer* Temp = Cast<ACPlayer>(GetPawn());
		FVector Location = Characters[1]->GetActorLocation();
		FRotator Rotation = Characters[1]->GetActorRotation();
		Characters[1]->SetActorLocation(GetPawn()->GetActorLocation());
		Characters[1]->SetActorRotation(GetPawn()->GetActorRotation());
		Possess(Cast<ACPlayer>(Characters[1]));
		Temp->SetActorLocation(Location);
		Temp->SetActorRotation(Rotation);
	}
	UE_LOG(LogTemp, Warning, TEXT("Change %s"), *GetNameSafe(Characters[1]));
}


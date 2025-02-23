#include "Character/CPlayerController.h"
#include "GameFramework/Character.h"
#include "Character/CPlayer.h"
#include "Kismet/GameplayStatics.h"

ACPlayerController::ACPlayerController()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPlayer::StaticClass(), CharacterArray);
	CharacterArray[0] = Cast<ACPlayer>(GetPawn());
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Change1", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter1);
	InputComponent->BindAction("Change2", EInputEvent::IE_Pressed, this, &ACPlayerController::ChangeCharacter2);
}

void ACPlayerController::AddCharacter(ACPlayer* InCharacter)
{
	CharacterArray.Add(InCharacter);
}

void ACPlayerController::ChangeCharacter1()
{
	if (ensure(CharacterArray[0] != nullptr))
	{
		CharacterArray[0]->SetActorLocation(GetPawn()->GetActorLocation());
		Possess(Cast<ACPlayer>(CharacterArray[0]));
	}
}

void ACPlayerController::ChangeCharacter2()
{
	if (ensure(CharacterArray[1] != nullptr))
	{
		CharacterArray[0]->SetActorLocation(GetPawn()->GetActorLocation());
		Possess(Cast<ACPlayer>(CharacterArray[1]));
	}
}


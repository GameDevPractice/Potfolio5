#include "CBTTaskSpeed.h"
#include "AI/CAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UCBTTaskSpeed::UCBTTaskSpeed()
{
	NodeName = TEXT("Speed");

}

EBTNodeResult::Type UCBTTaskSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* Panwn = AIC->GetPawn();
	if (Panwn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is nullptr in UCBTTaskAttack::ExecuteTask"));
		return EBTNodeResult::Failed;
	}
	ACharacter* Character = Cast<ACharacter>(Panwn);
	if (Character == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character is nullptr in UCBTTaskSpeed::ExecuteTask"));
		return EBTNodeResult::Failed;
	}
	Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	return EBTNodeResult::Succeeded;
}

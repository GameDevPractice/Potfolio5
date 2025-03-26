#include "Animation/CUnEquip.h"
#include "Character/CPlayer.h"

FString UCUnEquip::GetNotifyName() const
{
	return "UnEquip";
}

void UCUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player != nullptr)
	{
		Player->StartMovement();
	}
}

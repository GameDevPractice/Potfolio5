#include "Animation/CNotifyState_Collision.h"
#include "Character/CPlayer.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

FString UCNotifyState_Collision::GetNotifyName() const
{
	return "Collision";
}

void UCNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	ACPlayer* Player = Cast<ACPlayer>(Owner);
	if (Player == nullptr)
	{
		return;
	}
	UCapsuleComponent* CapsuleComponent = Player->GetCapsuleComponent();
	if (CapsuleComponent == nullptr)
	{
		return;
	}
	CapsuleComponent->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetRelativeTransform(Transform);

}

void UCNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	ACPlayer* Player = Cast<ACPlayer>(Owner);
	if (Player == nullptr)
	{
		return;
	}
	UCapsuleComponent* CapsuleComponent = Player->GetCapsuleComponent();
	if (CapsuleComponent == nullptr)
	{
		return;
	}
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

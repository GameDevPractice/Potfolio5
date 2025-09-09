#include "Character/CEnemy.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "Component/CMontageComponent.h"
#include "AI/CAIController.h"
#include "Components/CapsuleComponent.h"

ACEnemy::ACEnemy()
{
	bBoos = false;
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//AttackCollision
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollision"));
	Capsule->SetupAttachment(GetMesh());

	ActionComp = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComp"));
	AttributeComp = CreateDefaultSubobject<UCAttributeComponent>(TEXT("AttributeComp"));
	MontageComp = CreateDefaultSubobject<UCMontageComponent>(TEXT("MontageComp"));
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (ActorHasTag("Boos"))
	{
		bBoos = true;
	}
	
	AIC = GetController<ACAIController>();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnOverlapBegin);

}

bool ACEnemy::IsOwnHp_Implementation()
{
	return false;
}

void ACEnemy::SetVisibilityHp_Implementation(bool Visible)
{
}

void ACEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (OnBeginOverlap.IsBound())
	{
		//Bind Path is CAction_Melee
		OnBeginOverlap.Broadcast(OverlappedComp, SweepResult);
		return;
	}
}

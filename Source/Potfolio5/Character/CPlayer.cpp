#include "CPlayer.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/CActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 150.f));
	SpringArm->SetRelativeRotation(FRotator(-10.0f, 90.f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->TargetArmLength = 400.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationRoll = false;

	//Components
	ActionComp = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComp"));

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	bEquip = false;

	//Material
	 ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT(" / Script / Engine.Material'/Game/Itadori_aura/Material/M_NewMaterial1.M_NewMaterial1'"));
	 if (MaterialAsset.Succeeded())
	 {
		 OverlayMaterial = MaterialAsset.Object;
	 }
	 Overlapped = false;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind MovementEvent(Axis)
	PlayerInputComponent->BindAxis("Forward",this,&ACPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Right",this,&ACPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Pitch", this, &ACPlayer::PitchUp);
	PlayerInputComponent->BindAxis("Yaw", this, &ACPlayer::Yaw);

	//Bind ActionEvent
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::ActionJump);
	PlayerInputComponent->BindAction("FristAttack", IE_Pressed, this, &ACPlayer::FirstAttack_Implementation);
	PlayerInputComponent->BindAction("SecondAttack", IE_Pressed, this, &ACPlayer::SecondAttack_Implementation);
	PlayerInputComponent->BindAction("ThridAttack", IE_Pressed, this, &ACPlayer::ThridAttack);
	PlayerInputComponent->BindAction("ForthAttack", IE_Pressed, this, &ACPlayer::ForthAttack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACPlayer::StartSprint);
	PlayerInputComponent->BindAction("Run",IE_Released, this, &ACPlayer::StopSprint);
}

void ACPlayer::MoveForward(float Value)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetForwardVector();
	AddMovementInput(GetActorForwardVector(), Value);
}

void ACPlayer::MoveRight(float Value)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetRightVector();
	AddMovementInput(GetActorRightVector(), Value);
}

void ACPlayer::ActionJump()
{
	ActionComp->StartActionByName(this, "Jump");
	
}

void ACPlayer::PitchUp(float Vaule)
{
	AddControllerPitchInput(Vaule);
}

void ACPlayer::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void ACPlayer::Jump()
{
	Super::Jump();
}

void ACPlayer::StartMovement()
{
	GetCharacterMovement()->SetActive(true);
}

void ACPlayer::SetSpringArmTransform(FTransform NewTransform)
{
	SpringArm->SetWorldTransform(NewTransform);
}

void ACPlayer::StartSprint()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ACPlayer::StopSprint()
{
	ActionComp->StopActionByName(this, "Sprint");
}



void ACPlayer::FirstAttack_Implementation()
{
	ActionComp->StartActionByName(this, "First");
}

void ACPlayer::SecondAttack_Implementation()
{
	ActionComp->StartActionByName(this, "Second");
}

void ACPlayer::ThridAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ThridAttack"));
}

void ACPlayer::ForthAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ForthAttack"));
}

void ACPlayer::PlayEquip()
{
	bEquip = true;
	GetCharacterMovement()->SetActive(true);
	if (Overlapped)
	{
	GetMesh()->SetOverlayMaterial(OverlayMaterial);
	}
}

void ACPlayer::PlayUnEquip()
{
	if (!bEquip)
	{
		return;
	}
	if (UnEquipMontage != nullptr)
	{
		PlayAnimMontage(UnEquipMontage);
		GetCharacterMovement()->SetActive(false);
	}
	bEquip = false;
	if (Overlapped)
	{
	GetMesh()->SetOverlayMaterial(nullptr);
	}
}
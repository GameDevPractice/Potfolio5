#include "CPlayer.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/CActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 150.f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, 90.f, 0.0f));
	SpringArm->TargetArmLength = 200.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	//Components
	ActionComp = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComp"));

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	

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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("FristAttack", IE_Pressed, this, &ACPlayer::FirstAttack);
	PlayerInputComponent->BindAction("SecondAttack", IE_Pressed, this, &ACPlayer::SecondAttack);
	PlayerInputComponent->BindAction("ThridAttack", IE_Pressed, this, &ACPlayer::ThridAttack);
	PlayerInputComponent->BindAction("ForthAttack", IE_Pressed, this, &ACPlayer::ForthAttack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACPlayer::StartSprint);
	PlayerInputComponent->BindAction("Run",IE_Released, this, &ACPlayer::StopSprint);
}

void ACPlayer::MoveForward(float Value)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetForwardVector();
	AddMovementInput(Direction, Value);
}

void ACPlayer::MoveRight(float Value)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetRightVector();
	AddMovementInput(Direction, Value);
}

void ACPlayer::PitchUp(float Vaule)
{
	AddControllerPitchInput(Vaule);
}

void ACPlayer::Yaw(float Value)
{
	AddControllerYawInput(Value);
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
	UE_LOG(LogTemp, Log, TEXT("FirstAttack"));
}

void ACPlayer::SecondAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("SecondAttack"));
}

void ACPlayer::ThridAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ThridAttack"));
}

void ACPlayer::ForthAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ForthAttack"));
}
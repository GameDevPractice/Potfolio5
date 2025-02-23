#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCActionComponent;

UCLASS()
class POTFOLIO5_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	 
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchUp(float Vaule);
	void Yaw(float Value);

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	 void FirstAttack();
	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	 void SecondAttack();
	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	 void ThridAttack(); 
	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	 void ForthAttack() ;

protected:
	void StartSprint();
	void StopSprint();

	//Assets
protected:
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;
};

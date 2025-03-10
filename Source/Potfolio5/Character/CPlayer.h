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

//Movement

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void ActionJump();
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
	 void ForthAttack();

	void Jump();

protected:
	void StartSprint();
	void StopSprint();

protected:
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetImage() const { return Image; }

	//Assets, Component
protected:
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArm;


protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	UTexture2D* Image;

};

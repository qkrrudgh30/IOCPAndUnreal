// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SCharacterBase.h"
#include "InputActionValue.h"
#include "SPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREALGAME_API ASPlayerCharacter : public ASCharacterBase
{
	GENERATED_BODY()

#pragma region ASCharacterBase
	
public:
	ASPlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region ASPlayerCharacter
	
public:
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> FollowCamera;

#pragma endregion

#pragma region Input
	
protected:
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

public:	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookAction;

#pragma endregion

#pragma region MovementPacket
	
protected:
	static float MovePacketSendDelay;

	float AccDeltaTimeForSendingMovePacket = 0.f;

	FVector2D DesiredInput = FVector2D::ZeroVector;

	FVector DesiredMoveDirection = FVector::ZeroVector;

	float DesiredYaw = 0.f;

	FVector2D PreviousDesiredInput = FVector2D::ZeroVector;

#pragma endregion
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Protocol.pb.h"
#include "UnrealGame.h"
#include "Camera/CameraComponent.h"
#include "Game/SGameInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "ClientPacketHandler.h"

float ASPlayerCharacter::MovePacketSendDelay = 0.2f;

ASPlayerCharacter::ASPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASPlayerCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASPlayerCharacter::Look);
	}
}

void ASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool ForceSendPacket = false;

	if (PreviousDesiredInput != DesiredInput)
	{
		ForceSendPacket = true;
		PreviousDesiredInput = DesiredInput;
	}

	// State ����
	if (DesiredInput == FVector2D::Zero())
		SetMoveState(Protocol::MOVE_STATE_IDLE);
	else
		SetMoveState(Protocol::MOVE_STATE_RUN);

	AccDeltaTimeForSendingMovePacket += DeltaTime;

	if (MovePacketSendDelay <= AccDeltaTimeForSendingMovePacket || ForceSendPacket)
	{
		AccDeltaTimeForSendingMovePacket = 0.f;

		Protocol::C_MOVE MovePkt;

		{
			Protocol::PosInfo* Info = MovePkt.mutable_info();
			Info->CopyFrom(*CurrentCharacterPosInfo);
			Info->set_yaw(DesiredYaw);
			Info->set_state(GetMoveState());
		}

		//SEND_PACKET(MovePkt);
		
		// USSendBufferSharedPtr SendBuffer2 = SClientPacketHandler::MakePacket(MovePkt);
		// Cast<USGameInstance>(GWorld->GetGameInstance())->SendPacket(SendBuffer2);
	}
}

void ASPlayerCharacter::Move(const FInputActionValue& Value)
{
}

void ASPlayerCharacter::Look(const FInputActionValue& Value)
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/SCharacterBase.h"
#include "Engine/GameInstance.h"
#include "UnrealGame.h"
#include "SGameInstance.generated.h"

class ASPlayerCharacter;
class ASCharacterBase;
/**
 * 
 */
UCLASS()
class UNREALGAME_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void Shutdown() override;

protected:
	void ConnectToServer();

	void DisconnectFromServer();

	void HandleRecvPackets();

	void SendPacket(USSendBufferSharedPtr InSendBuffer);

public:
	FSocket* ClientSocket = nullptr;
	
	FString ServerIPAddress = TEXT("127.0.0.1");

	int16 ServerPortNumber = 8888;

	TSharedPtr<USPacketSession> ServerSession;

public:
	UPROPERTY()
	TObjectPtr<ASPlayerCharacter> OwnerPlayerCharacter = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASCharacterBase> OtherCharacterClass = ASCharacterBase::StaticClass();

	TMap<uint64, TObjectPtr<ASCharacterBase>> Characters;
	
};

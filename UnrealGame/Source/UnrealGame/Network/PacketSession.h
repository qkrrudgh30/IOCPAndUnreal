// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UnrealGame.h"

class FSocket;
class USRecvWorker;
class USSendWorker;

class UNREALGAME_API USPacketSession : public TSharedFromThis<USPacketSession>
{
public:
	USPacketSession(FSocket* InSocket);
	~USPacketSession();

public:
	void Run();

	void HandleRecvPackets();

	void Disconnect();
	
	void SendPacket(USSendBufferSharedPtr InSendBuffer);
		// 이 함수에는 UFUNCTION() 매크로를 붙히면 안됨. UObejct를 상속 받지 않았기 때문.

public:
	FSocket* Socket;

	TSharedPtr<USRecvWorker> RecvWorker;
	
	TQueue<TArray<uint8>> RecvPacketQueue;
	
	TSharedPtr<USSendWorker> SendWorker;
	
	TQueue<USSendBufferSharedPtr> SendPacketQueue;
	
};

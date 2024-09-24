// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UnrealGame.h"

class FSocket;
class USPacketSession;

// TCP 통신의 경우 PacketHeader를 두는 것이 거의 국룰.
// 데이터의 경계 개념이 없기 때문. Header를 통해 해당 패킷의 전체 크기를 알 수 있게끔 해야함.
struct UNREALGAME_API FPacketHeader
{
	FPacketHeader()
		: PacketSize(0)
		, PacketID(0)
	{
	}

	FPacketHeader(uint16 PacketSize, uint16 PacketID)
		: PacketSize(PacketSize)
		, PacketID(PacketID)
	{
	}

	friend FArchive& operator<<(FArchive& Ar, FPacketHeader& Header)
	{
		Ar << Header.PacketSize;
		Ar << Header.PacketID;
		return Ar;
	}

	uint16 PacketSize; // 멤버의 순서도 아주 중요함.
	uint16 PacketID;
};

// Recv 패킷을 조립하는 스레드.
class UNREALGAME_API USRecvWorker : public FRunnable
{
public:
	USRecvWorker(FSocket* InSocket, TSharedPtr<USPacketSession> InSession);
	
	~USRecvWorker();

	virtual bool Init() override;
	
	virtual uint32 Run() override;
	
	virtual void Exit() override;

	void Destroy();
	
private:
	bool ReceivePacket(TArray<uint8>& OutPacket);
	
	bool ReceiveDesiredBytes(uint8* OutResults, int32 InSize);
		// 내가 원하는 크기의 패킷이 올때까지(패킷 크기만큼 다 받아질때까지)기다리는 함수. 다 받으면 Results에 담아줌.

protected:
	FRunnableThread* Thread = nullptr;
	
	bool bIsRunning = true; // 밖(GameInstance)에서 Running을 false로 꺼버리면 해당 스레드도 종료되는 방식.
	
	FSocket* Socket;
	
	TWeakPtr<USPacketSession> SessionRef;
};

class UNREALGAME_API USSendWorker : public FRunnable
{
public:
	USSendWorker(FSocket* InSocket, TSharedPtr<USPacketSession> InSession);
	
	~USSendWorker();

	virtual bool Init() override;
	
	virtual uint32 Run() override;
	
	virtual void Exit() override;

	bool SendPacket(USSendBufferSharedPtr InSendBuffer);

	void Destroy();

private:
	bool SendDesiredBytes(const uint8* InBuffer, int32 InSize);

protected:
	FRunnableThread* Thread = nullptr;
	
	bool bIsRunning = true;
	
	FSocket* Socket;
	
	TWeakPtr<USPacketSession> SessionRef;
	
};

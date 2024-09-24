// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct USPacketHeader
{
	uint16 PacketSize;
	uint16 PacketID;
};

class USSendBuffer : public TSharedFromThis<USSendBuffer>
{
public:
	USSendBuffer(int32 InBufferSize);
	~USSendBuffer();

	BYTE* GetBuffer() { return Buffer.GetData(); }
	uint32 GetWriteSize() { return WriteSize; }
	uint32 GetCapacity() { return static_cast<int32>(Buffer.Num()); }

	void CopyData(void* InData, int32 InLength);
	void Close(uint32 InWriteSize);

private:
	TArray<BYTE> Buffer;
	
	uint32 WriteSize = 0;

};

#define DEFINE_SHARED_PTR(InClassName) using InClassName##SharedPtr = TSharedPtr<class InClassName>;

DEFINE_SHARED_PTR(USSession);
DEFINE_SHARED_PTR(USPacketSession);
DEFINE_SHARED_PTR(USSendBuffer);

#define SEND_PACKET(Pkt)                                                      \
	USSendBufferSharedPtr SendBuffer = SClientPacketHandler::MakePacket(Pkt);  \
	Cast<USGameInstance>(GWorld->GetGameInstance())->SendPacket(SendBuffer);
	
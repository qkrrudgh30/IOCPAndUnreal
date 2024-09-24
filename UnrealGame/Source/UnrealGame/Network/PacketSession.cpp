// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketSession.h"
#include "UnrealGame.h"
#include "NetworkWorker.h"
#include "ClientPacketHandler.h"


USPacketSession::USPacketSession(FSocket* InSocket)
	: Socket(InSocket)
{
	USClientPacketHandler::Init();
}

USPacketSession::~USPacketSession()
{
	Disconnect();
}

void USPacketSession::Run()
{
	RecvWorker = MakeShared<USRecvWorker>(Socket, AsShared());
	SendWorker = MakeShared<USSendWorker>(Socket, AsShared());
}

void USPacketSession::HandleRecvPackets()
{
	while (true)
	{
		TArray<uint8> Packet;
		if (RecvPacketQueue.Dequeue(OUT Packet) == false)
			break;

		// 여기부터는 recv 패킷을 꺼내온 상태.
		// 해당 패킷을 처리할때는 패킷의 번호를 보고, 번호에 맞는 함수를 호출하면서 해당 패킷을 인자로 전달해주는 식으로 구현함.
		// 조금 아쉬운 프로젝트에서는 이를 switch-case 문으로 처리함. case가 몇백개씩 늘어남.
		// 우리는 나중에 ClientPacketHandler 클래스에서 이를 처리할 예정.
	}
}

void USPacketSession::Disconnect()
{
	if (RecvWorker)
	{
		RecvWorker->Destroy();
		RecvWorker = nullptr;
	}

	if (SendWorker)
	{
		SendWorker->Destroy(); // 스레드를 깜빡하고 안끈 상태로 다시 언리얼을 켜서 PIE 하게 되면 크래시남.
		SendWorker = nullptr;
	}
}

void USPacketSession::SendPacket(USSendBufferSharedPtr InSendBuffer)
{
	SendPacketQueue.Enqueue(InSendBuffer);
}

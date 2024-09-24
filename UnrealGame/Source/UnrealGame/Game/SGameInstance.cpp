// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameInstance.h"
#include "UnrealGame.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"

void USGameInstance::Init()
{
	Super::Init();

	ConnectToServer();
}

void USGameInstance::Shutdown()
{
	Super::Shutdown();

	DisconnectFromServer();
}

void USGameInstance::ConnectToServer()
{
	ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("ClientSocket"));

	FIPv4Address IPAddressToConnect;
	FIPv4Address::Parse(ServerIPAddress, IPAddressToConnect);

	TSharedRef<FInternetAddr> AddressToConnect = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	AddressToConnect->SetIp(IPAddressToConnect.Value);
	AddressToConnect->SetPort(ServerPortNumber);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connecting to server...")));

	bool bIsConnected = ClientSocket->Connect(*AddressToConnect);
	if (bIsConnected == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Success.")));

		// ServerSession = MakeShared<USPacketSession>(ClientSocket);
		// ServerSession->Run();
		//
		// // TEMP : Lobby���� ĳ���� ����â ��
		// {
		// 	Protocol::C_LOGIN Pkt;
		// 	SendBufferRef SendBuffer = ClientPacketHandler::MakeSendBuffer(Pkt);
		// 	SendPacket(SendBuffer);
		// }
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Failed.")));
	}
}

void USGameInstance::DisconnectFromServer()
{
	if (ClientSocket != nullptr)
	{
		ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();
		SocketSubsystem->DestroySocket(ClientSocket);
		ClientSocket = nullptr;
	}
}

void USGameInstance::HandleRecvPackets()
{
}

void USGameInstance::SendPacket(USSendBufferSharedPtr InSendBuffer)
{
}

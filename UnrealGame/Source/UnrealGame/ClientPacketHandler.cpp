#include "ClientPacketHandler.h"
#include "UnrealGame.h"
#include "ReadableBuffer.h"

USPacketHandlerFunctionType GPacketHandlerFunctions[UINT16_MAX];

bool Handle_INVALID(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength)
{
	return false;
}

bool Handle_S_LOGIN(USPacketSessionSharedPtr& InPacketSession, Protocol::S_LOGIN& InPacket)
{
	for (auto& Player : InPacket.players())
	{
	}

	for (int32 i = 0; i < InPacket.players_size(); i++)
	{
		const Protocol::ObjectInfo& Player = InPacket.players(i);
	}

	Protocol::C_ENTER_GAME EnterGamePkt;
	EnterGamePkt.set_playerindex(0);
	//SEND_PACKET(EnterGamePkt);

	return true;
}

bool Handle_S_ENTER_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::S_ENTER_GAME& InPacket)
{
	// if (auto* GameInstance = Cast<US1GameInstance>(GWorld->GetGameInstance()))
	// {
	// 	GameInstance->HandleSpawn(InPacket);
	// }

	return true;
}

bool Handle_S_LEAVE_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::S_LEAVE_GAME& InPacket)
{
	// if (auto* GameInstance = Cast<US1GameInstance>(GWorld->GetGameInstance()))
	// {
	// }

	return true;
}

bool Handle_S_SPAWN(USPacketSessionSharedPtr& InPacketSession, Protocol::S_SPAWN& InPacket)
{
	// if (auto* GameInstance = Cast<US1GameInstance>(GWorld->GetGameInstance()))
	// {
	// 	GameInstance->HandleSpawn(InPacket);
	// }

	return true;
}

bool Handle_S_DESPAWN(USPacketSessionSharedPtr& InPacketSession, Protocol::S_DESPAWN& InPacket)
{
	// if (auto* GameInstance = Cast<US1GameInstance>(GWorld->GetGameInstance()))
	// {
	// 	GameInstance->HandleDespawn(InPacket);
	// }

	return true;
}

bool Handle_S_MOVE(USPacketSessionSharedPtr& InPacketSession, Protocol::S_MOVE& InPacket)
{
	// if (auto* GameInstance = Cast<US1GameInstance>(GWorld->GetGameInstance()))
	// {
	// 	GameInstance->HandleMove(InPacket);
	// }

	return true;
}

bool Handle_S_CHAT(USPacketSessionSharedPtr& InPacketSession, Protocol::S_CHAT& InPacket)
{
	auto Msg = InPacket.msg();
	
	return true;
}

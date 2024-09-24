#include "pch.h"
#include "ServerPacketHandler.h"
#include "ReadableBuffer.h"
#include "WritableBuffer.h"
#include "Protocol.pb.h"
#include "Room.h"
#include "ObjectManager.h"
#include "PlayerCharacter.h"
#include "ClientSession.h"
#include "Utils.h"

USPacketHandlerFunctionType GPacketHandlerFunctions[UINT16_MAX];

bool Handle_INVALID(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength)
{
	USPacketHeader* Header = reinterpret_cast<USPacketHeader*>(InBuffer);
	return false;
}

bool Handle_C_LOGIN(USPacketSessionSharedPtr& InPacketSession, Protocol::C_LOGIN& InPacket)
{
	Protocol::S_LOGIN loginPkt;

	for (int32 i = 0; i < 3; i++)
	{
		Protocol::ObjectInfo* player = loginPkt.add_players();
		Protocol::PosInfo* posInfo = player->mutable_pos_info();
		posInfo->set_x(USUtils::GetRandom(0.f, 100.f));
		posInfo->set_y(USUtils::GetRandom(0.f, 100.f));
		posInfo->set_z(USUtils::GetRandom(0.f, 100.f));
		posInfo->set_yaw(USUtils::GetRandom(0.f, 45.f));
	}

	loginPkt.set_success(true);

	SEND_PACKET(loginPkt);

	return true;
}

bool Handle_C_ENTER_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::C_ENTER_GAME& InPacket)
{
	USPlayerCharacterSharedPtr player = USObjectManager::CreatePlayer(static_pointer_cast<USClientSession>(InPacketSession));

	GRoom->DoAsync(&USRoom::HandleEnterPlayer, player);

	return true;
}

bool Handle_C_LEAVE_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::C_LEAVE_GAME& InPacket)
{
	auto gameSession = static_pointer_cast<USClientSession>(InPacketSession);

	USPlayerCharacterSharedPtr player = gameSession->Player.load();
	if (player == nullptr)
		return false;

	USRoomSharedPtr room = player->Room.load().lock();
	if (room == nullptr)
		return false;

	room->HandleLeavePlayer(player);

	return true;
}

bool Handle_C_MOVE(USPacketSessionSharedPtr& InPacketSession, Protocol::C_MOVE& InPacket)
{
	auto gameSession = static_pointer_cast<USClientSession>(InPacketSession);

	USPlayerCharacterSharedPtr player = gameSession->Player.load();
	if (player == nullptr)
		return false;

	USRoomSharedPtr room = player->Room.load().lock();
	if (room == nullptr)
		return false;

	room->DoAsync(&USRoom::HandleMove, InPacket);

	return true;
}

bool Handle_C_CHAT(USPacketSessionSharedPtr& InPacketSession, Protocol::C_CHAT& InPacket)
{
	return false;
}

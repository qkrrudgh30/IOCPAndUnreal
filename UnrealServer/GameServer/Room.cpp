#include "pch.h"
#include "Room.h"
#include "PlayerCharacter.h"
#include "ClientSession.h"
#include "ObjectManager.h"
#include "Utils.h"
#include "ServerPacketHandler.h"

USRoomSharedPtr GRoom = make_shared<USRoom>();

USRoom::USRoom()
{
}

USRoom::~USRoom()
{
}

bool USRoom::EnterRoom(USObjectSharedPtr InObject, bool InUseRandPos)
{
	bool success = AddObject(InObject);

	if (InUseRandPos)
	{
		InObject->PosInfo->set_x(USUtils::GetRandom(0.f, 500.f));
		InObject->PosInfo->set_y(USUtils::GetRandom(0.f, 500.f));
		InObject->PosInfo->set_z(100.f);
		InObject->PosInfo->set_yaw(USUtils::GetRandom(0.f, 100.f));
	}

	if (auto player = dynamic_pointer_cast<USPlayerCharacter>(InObject))
	{
		Protocol::S_ENTER_GAME enterGamePkt;
		enterGamePkt.set_success(success);

		Protocol::ObjectInfo* playerInfo = new Protocol::ObjectInfo();
		playerInfo->CopyFrom(*InObject->ObjectInfo);
		enterGamePkt.set_allocated_player(playerInfo);

		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(enterGamePkt);
		if (auto session = player->ClientSession.lock())
			session->Send(sendBuffer);
	}

	{
		Protocol::S_SPAWN spawnPkt;

		Protocol::ObjectInfo* objectInfo = spawnPkt.add_players();
		objectInfo->CopyFrom(*InObject->ObjectInfo);

		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(spawnPkt);
		Broadcast(sendBuffer, InObject->ObjectInfo->object_id());
	}

	if (auto player = dynamic_pointer_cast<USPlayerCharacter>(InObject))
	{
		Protocol::S_SPAWN spawnPkt;

		for (auto& item : Objects)
		{
			if (item.second->IsPlayer() == false)
				continue;

			Protocol::ObjectInfo* playerInfo = spawnPkt.add_players();
			playerInfo->CopyFrom(*item.second->ObjectInfo);
		}

		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(spawnPkt);
		if (auto session = player->ClientSession.lock())
			session->Send(sendBuffer);
	}

	return success;
}

bool USRoom::LeaveRoom(USObjectSharedPtr InObject)
{
	if (InObject == nullptr)
		return false;

	const uint64 objectId = InObject->ObjectInfo->object_id();
	bool success = RemoveObject(objectId);

	if (auto player = dynamic_pointer_cast<USPlayerCharacter>(InObject))
	{
		Protocol::S_LEAVE_GAME leaveGamePkt;

		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(leaveGamePkt);
		if (auto session = player->ClientSession.lock())
			session->Send(sendBuffer);
	}

	{
		Protocol::S_DESPAWN despawnPkt;
		despawnPkt.add_object_ids(objectId);

		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(despawnPkt);
		Broadcast(sendBuffer, objectId);

		if (auto player = dynamic_pointer_cast<USPlayerCharacter>(InObject))
			if (auto session = player->ClientSession.lock())
				session->Send(sendBuffer);
	}

	return success;
}

bool USRoom::HandleEnterPlayer(USPlayerCharacterSharedPtr InPlayer)
{
	return EnterRoom(InPlayer, true);
}

bool USRoom::HandleLeavePlayer(USPlayerCharacterSharedPtr InPlayer)
{
	return LeaveRoom(InPlayer);
}

void USRoom::HandleMove(Protocol::C_MOVE InMovePacket)
{
	const uint64 objectId = InMovePacket.info().object_id();
	if (Objects.find(objectId) == Objects.end())
		return;

	USPlayerCharacterSharedPtr player = dynamic_pointer_cast<USPlayerCharacter>(Objects[objectId]);
	player->PosInfo->CopyFrom(InMovePacket.info());

	{
		Protocol::S_MOVE movePkt;
		{
			Protocol::PosInfo* info = movePkt.mutable_info();
			info->CopyFrom(InMovePacket.info());
		}
		USSendBufferSharedPtr sendBuffer = USServerPacketHandler::MakePacket(movePkt);
		Broadcast(sendBuffer);
	}
}

void USRoom::UpdateTick()
{
	cout << "Update Room" << endl;

	DoTimer(100, &USRoom::UpdateTick);
}

USRoomSharedPtr USRoom::GetRoomRef()
{
	return static_pointer_cast<USRoom>(shared_from_this());
}

bool USRoom::AddObject(USObjectSharedPtr InObject)
{
	if (Objects.find(InObject->ObjectInfo->object_id()) != Objects.end())
		return false;

	Objects.insert(make_pair(InObject->ObjectInfo->object_id(), InObject));

	InObject->Room.store(GetRoomRef());

	return true;
}

bool USRoom::RemoveObject(uint64 InObjectID)
{
	if (Objects.find(InObjectID) == Objects.end())
		return false;

	USObjectSharedPtr InObject = Objects[InObjectID];
	USPlayerCharacterSharedPtr player = dynamic_pointer_cast<USPlayerCharacter>(InObject);
	if (player)
		player->Room.store(weak_ptr<USRoom>());

	Objects.erase(InObjectID);

	return true;
}

void USRoom::Broadcast(USSendBufferSharedPtr InSendBuffer, uint64 InExceptedID)
{
	for (auto& item : Objects)
	{
		USPlayerCharacterSharedPtr player = dynamic_pointer_cast<USPlayerCharacter>(item.second);
		if (player == nullptr)
			continue;
		if (player->ObjectInfo->object_id() == InExceptedID)
			continue;

		if (USClientSessionSharedPtr session = player->ClientSession.lock())
			session->Send(InSendBuffer);
	}
}

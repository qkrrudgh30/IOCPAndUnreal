#pragma once

#include "JobQueue.h"

class USRoom : public USJobQueue
{
public:
	USRoom();
	virtual ~USRoom();

public:
	bool EnterRoom(USObjectSharedPtr InObject, bool InUseRandPos = true);
	bool LeaveRoom(USObjectSharedPtr InObject);

	bool HandleEnterPlayer(USPlayerCharacterSharedPtr InPlayer);
	bool HandleLeavePlayer(USPlayerCharacterSharedPtr InPlayer);
	void HandleMove(Protocol::C_MOVE InMovePacket);

public:
	void UpdateTick();

	USRoomSharedPtr GetRoomRef();

private:
	bool AddObject(USObjectSharedPtr InObject);
	bool RemoveObject(uint64 InObjectID);

private:
	void Broadcast(USSendBufferSharedPtr InSendBuffer, uint64 InExceptedID = 0);

private:
	unordered_map<uint64, USObjectSharedPtr> Objects;

};

extern USRoomSharedPtr GRoom;

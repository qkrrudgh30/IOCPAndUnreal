#include "pch.h"
#include "ObjectManager.h"
#include "Object.h"
#include "PlayerCharacter.h"
#include "ClientSession.h"

atomic<int64> USObjectManager::IDGenerator = 1;

USPlayerCharacterSharedPtr USObjectManager::CreatePlayer(USClientSessionSharedPtr InClientSession)
{
	const int64 NewID = IDGenerator.fetch_add(1);

	USPlayerCharacterSharedPtr NewCharacter = make_shared<USPlayerCharacter>();
	NewCharacter->ObjectInfo->set_object_id(NewID);
	NewCharacter->PosInfo->set_object_id(NewID);

	NewCharacter->ClientSession = InClientSession;
	InClientSession->Player.store(NewCharacter);
	
	return NewCharacter;
}

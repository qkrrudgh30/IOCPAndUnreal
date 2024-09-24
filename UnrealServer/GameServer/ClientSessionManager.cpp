#include "pch.h"
#include "ClientSessionManager.h"
#include "ClientSession.h"

USClientSessionManager GClientSessionManager;

void USClientSessionManager::Add(USClientSessionSharedPtr InClientSession)
{
	WRITE_LOCK;
	ClientSessions.insert(InClientSession);
}

void USClientSessionManager::Remove(USClientSessionSharedPtr InClientSession)
{
	WRITE_LOCK;
	ClientSessions.erase(InClientSession);
}

void USClientSessionManager::Broadcast(USSendBufferSharedPtr InSendBuffer)
{
	WRITE_LOCK;
	for (USClientSessionSharedPtr ClientSession : ClientSessions)
	{
		ClientSession->Send(InSendBuffer);
	}
}

#pragma once

class USGameSession;

using USClientSessionSharedPtr = shared_ptr<USClientSession>;

class USClientSessionManager
{
public:
	void Add(USClientSessionSharedPtr InClientSession);
	void Remove(USClientSessionSharedPtr InClientSession);
	void Broadcast(USSendBufferSharedPtr InSendBuffer);

private:
	USE_LOCK;
	set<USClientSessionSharedPtr> ClientSessions;

};

extern USClientSessionManager GClientSessionManager;

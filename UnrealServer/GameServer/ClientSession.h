#pragma once
#include "Session.h"

class USPlayerCharacter;

class USClientSession : public USPacketSession
{
public:
	~USClientSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* InBuffer, int32 InBufferLength) override;
	virtual void OnSend(int32 InLength) override;

public:
	atomic<shared_ptr<USPlayerCharacter>> Player;

};


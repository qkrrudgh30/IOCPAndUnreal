#include "pch.h"
#include "ClientSession.h"
#include "ClientSessionManager.h"
#include "Room.h"

void USClientSession::OnConnected()
{
	GClientSessionManager.Add(static_pointer_cast<USClientSession>(shared_from_this()));
}

void USClientSession::OnDisconnected()
{
	GClientSessionManager.Remove(static_pointer_cast<USClientSession>(shared_from_this()));
}

void USClientSession::OnRecvPacket(BYTE* InBuffer, int32 InBufferLength)
{
	USPacketSessionSharedPtr Session = GetPacketSessionRef();
	USPacketHeader* PacketHeader = reinterpret_cast<USPacketHeader*>(InBuffer);

	USServerPacketHandler::HandlePacket(Session, InBuffer, InBufferLength);
}

void USClientSession::OnSend(int32 InLength)
{
}

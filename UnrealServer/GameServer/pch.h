#pragma once

// �Ʒ� �ڵ�� ������Ʈ �Ӽ� > ��Ŀ > �Է� > �߰� ���Ӽ��� �߰��ϴ� �Ͱ� ������ ȿ��. �߰� ���Ӽ��� ServerCore.lib�� �־�ǳ�, �װ� ��� �Ʒ� �ڵ带 �ۼ��ص���.
#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib") 
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib") 

#else 
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")

#endif // _DEBUG

#include "CorePCH.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include "ServerPacketHandler.h"
#include "ClientSession.h"

DEFINE_SHARED_PTR(USClientSession);
DEFINE_SHARED_PTR(USObject);
DEFINE_SHARED_PTR(USCharacterBase);
DEFINE_SHARED_PTR(USRoom);
DEFINE_SHARED_PTR(USPlayerCharacter);

#define SEND_PACKET(pkt)													\
	USSendBufferSharedPtr BufferToSend = USServerPacketHandler::MakePacket(pkt);	\
	InPacketSession->Send(BufferToSend);

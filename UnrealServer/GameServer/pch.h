#pragma once

// 아래 코드는 프로젝트 속성 > 링커 > 입력 > 추가 종속성에 추가하는 것과 동일한 효과. 추가 종속성에 ServerCore.lib를 넣어도되나, 그거 대신 아래 코드를 작성해도됨.
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

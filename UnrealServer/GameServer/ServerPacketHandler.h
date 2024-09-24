#pragma once
#include "Protocol.pb.h"

#if 1 <= UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING
#include "UnrealGame.h"
#endif

using USPacketHandlerFunctionType = std::function<bool(USPacketSessionSharedPtr&, BYTE*, int32)>;
extern USPacketHandlerFunctionType GPacketHandlerFunctions[UINT16_MAX];

enum : uint16
{
    PKT_C_LOGIN = 1000,
    PKT_S_LOGIN = 1001,
    PKT_C_ENTER_GAME = 1002,
    PKT_S_ENTER_GAME = 1003,
    PKT_C_LEAVE_GAME = 1004,
    PKT_S_LEAVE_GAME = 1005,
    PKT_S_SPAWN = 1006,
    PKT_S_DESPAWN = 1007,
    PKT_C_MOVE = 1008,
    PKT_S_MOVE = 1009,
    PKT_C_CHAT = 1010,
    PKT_S_CHAT = 1011,
};

// Custom Handlers
bool Handle_INVALID(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength);
bool Handle_C_LOGIN(USPacketSessionSharedPtr& InPacketSession, Protocol::C_LOGIN& InPacket);
bool Handle_C_ENTER_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::C_ENTER_GAME& InPacket);
bool Handle_C_LEAVE_GAME(USPacketSessionSharedPtr& InPacketSession, Protocol::C_LEAVE_GAME& InPacket);
bool Handle_C_MOVE(USPacketSessionSharedPtr& InPacketSession, Protocol::C_MOVE& InPacket);
bool Handle_C_CHAT(USPacketSessionSharedPtr& InPacketSession, Protocol::C_CHAT& InPacket);

class USServerPacketHandler
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++)
            GPacketHandlerFunctions[i] = Handle_INVALID;
        GPacketHandlerFunctions[PKT_C_LOGIN] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, InPacketSession, InBuffer, InBufferLength); };
        GPacketHandlerFunctions[PKT_C_ENTER_GAME] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::C_ENTER_GAME>(Handle_C_ENTER_GAME, InPacketSession, InBuffer, InBufferLength); };
        GPacketHandlerFunctions[PKT_C_LEAVE_GAME] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::C_LEAVE_GAME>(Handle_C_LEAVE_GAME, InPacketSession, InBuffer, InBufferLength); };
        GPacketHandlerFunctions[PKT_C_MOVE] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::C_MOVE>(Handle_C_MOVE, InPacketSession, InBuffer, InBufferLength); };
        GPacketHandlerFunctions[PKT_C_CHAT] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::C_CHAT>(Handle_C_CHAT, InPacketSession, InBuffer, InBufferLength); };
    }

    static bool HandlePacket(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength)
    {
        USPacketHeader* PacketHeader = reinterpret_cast<USPacketHeader*>(InBuffer);
        return GPacketHandlerFunctions[PacketHeader->PacketID](InPacketSession, InBuffer, InBufferLength);
    }
    static USSendBufferSharedPtr MakePacket(Protocol::S_LOGIN&InPacket) { return MakePacket(InPacket, PKT_S_LOGIN); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_ENTER_GAME&InPacket) { return MakePacket(InPacket, PKT_S_ENTER_GAME); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_LEAVE_GAME&InPacket) { return MakePacket(InPacket, PKT_S_LEAVE_GAME); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_SPAWN&InPacket) { return MakePacket(InPacket, PKT_S_SPAWN); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_DESPAWN&InPacket) { return MakePacket(InPacket, PKT_S_DESPAWN); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_MOVE&InPacket) { return MakePacket(InPacket, PKT_S_MOVE); }
    static USSendBufferSharedPtr MakePacket(Protocol::S_CHAT&InPacket) { return MakePacket(InPacket, PKT_S_CHAT); }

private:
    template<typename PacketType, typename CallbackFunctionType>
    static bool HandlePacket(CallbackFunctionType InCallbackFunction, USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength)
    {
        PacketType Type;
        if (Type.ParseFromArray(InBuffer + sizeof(USPacketHeader), InBufferLength - sizeof(USPacketHeader)) == false)
            return false;

        return InCallbackFunction(InPacketSession, Type);
    }

    template<typename T>
    static USSendBufferSharedPtr MakePacket(T& InPacket, uint16 InPacketID)
    {
        const uint16 DataSize = static_cast<uint16>(InPacket.ByteSizeLong());
        const uint16 PacketSize = DataSize + sizeof(USPacketHeader);

#if 1 <= UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING
        USSendBufferSharedPtr BufferToSend = MakeShared<USSendBuffer>(PacketSize);
#else
        USSendBufferSharedPtr BufferToSend = make_shared<USSendBuffer>(PacketSize);
#endif
        USPacketHeader* PacketHeader = reinterpret_cast<USPacketHeader*>(BufferToSend->GetBuffer());
        PacketHeader->PacketSize = PacketSize;
        PacketHeader->PacketID = InPacketID;
        InPacket.SerializeToArray(&PacketHeader[1], DataSize);
        BufferToSend->Close(PacketSize);

        return BufferToSend;
    }
};
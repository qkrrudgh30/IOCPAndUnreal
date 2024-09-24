#pragma once
#include "Protocol.pb.h"

#if 1 <= UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING
#include "UnrealGame.h"
#endif

using USPacketHandlerFunctionType = std::function<bool(USPacketSessionSharedPtr&, BYTE*, int32)>;
extern USPacketHandlerFunctionType GPacketHandlerFunctions[UINT16_MAX];

enum : uint16
{
{%- for pkt in parser.total_pkt %}
    PKT_{{pkt.name}} = {{pkt.id}},
{%- endfor %}
};

// Custom Handlers
bool Handle_INVALID(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength);

{%- for pkt in parser.recv_pkt %}
bool Handle_{{pkt.name}}(USPacketSessionSharedPtr& InPacketSession, Protocol::{{pkt.name}}& InPacket);
{%- endfor %}

class S{{output}}
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++)
            GPacketHandlerFunctions[i] = Handle_INVALID;

{%- for pkt in parser.recv_pkt %}
        GPacketHandlerFunctions[PKT_{{pkt.name}}] = [](USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength) { return HandlePacket<Protocol::{{pkt.name}}>(Handle_{{pkt.name}}, InPacketSession, InBuffer, InBufferLength); };
{%- endfor %}
    }

    static bool HandlePacket(USPacketSessionSharedPtr& InPacketSession, BYTE* InBuffer, int32 InBufferLength)
    {
        USPacketHeader* PacketHeader = reinterpret_cast<USPacketHeader*>(InBuffer);
        return GPacketHandlerFunctions[PacketHeader->PacketID](InPacketSession, InBuffer, InBufferLength);
    }

{%- for pkt in parser.send_pkt %}
    static USSendBufferSharedPtr MakePacket(Protocol::{{pkt.name}}&InPacket) { return MakePacket(InPacket, PKT_{{pkt.name}}); }
{%- endfor %}

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

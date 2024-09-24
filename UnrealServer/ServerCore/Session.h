#pragma once

#include "IOCPCore.h"
#include "IOCPEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

struct USPacketHeader
{
    uint16 PacketSize; // 특정 패킷에 가변적인 데이터(이름, 문자열, 주변모든 유저들에게 보내줘야하는 데이터, ...)때문에 size 필요.
    uint16 PacketID; // 프로토콜ID (ex. 1=로그인, 2=이동요청, ...)
    // [size(2)][id(2)][data....][size(2)][id(2)][data....]...
};

class USSession : public USIOCPObject
{
    friend class SReceptionist;
    friend class SIOCPCore;
    friend class SService;

    enum
    {
        BUFFER_SIZE = 0x10000, // 64KB
    };

public:
    USSession();

    virtual ~USSession();

public:
    /* 정보 관련 */
    void SetClientAddress(USNetAddress InClientAddress) { ClientAddress = InClientAddress; }

    USNetAddress GetClientAddress() { return ClientAddress; }

    SOCKET GetClientHandlerSocket() { return ClientHandlerSocket; }

public:
    virtual HANDLE GetHandle() override;

    virtual void Dispatch(class USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes = 0) override;

public:
    void Disconnect(const WCHAR* InCause);

    shared_ptr<class USService> GetService() { return Service.lock(); }

    void SetService(shared_ptr<USService> InService) { Service = InService; }

public:
    bool IsConnected() { return IsClientConnected; }

    USSessionSharedPtr GetSessionRef() { return static_pointer_cast<USSession>(shared_from_this()); }

public:
    bool				RegisterConnect();
    void				RegisterRecv();
    void				RegisterSend();
    bool				RegisterDisconnect();

    void				ProcessConnect();
    void				ProcessRecv(int32 InNumberOfBytes);
    void				ProcessSend(int32 InNumberOfBytes);
    void				ProcessDisconnect();

    void				HandleError(int32 InErrorCode);

protected:
    virtual void		OnConnected() { }
    virtual int32		OnRecv(BYTE* InBuffer, int32 InLength) { return InLength; }
    virtual void		OnSend(int32 InLength) { }
    virtual void		OnDisconnected() { }

public:
    void				Send(USSendBufferSharedPtr InSendBuffer);

    bool				Connect();

public:
    USRecvBuffer RecvBuffer;

private:
    SOCKET ClientHandlerSocket = INVALID_SOCKET;

    USNetAddress	ClientAddress = {};

    atomic<bool> IsClientConnected = false;

    weak_ptr<class USService> Service;

    USE_LOCK;

    USRecvEvent RecvEvent;

    USConnectEvent		ConnectEvent;

    USDisconnectEvent		DisconnectEvent;

    queue<USSendBufferSharedPtr> SendBufferQueue;

    atomic<bool> bIsSendBufferRegistered = false;

    USSendEvent SendEvent;

};

class USPacketSession : public USSession
{
public:
    USPacketSession();
    virtual ~USPacketSession();

    USPacketSessionSharedPtr GetPacketSessionRef() { return static_pointer_cast<USPacketSession>(shared_from_this()); }

protected:
    virtual int32		OnRecv(BYTE* InBuffer, int32 InBufferLength) final;
    virtual void		OnRecvPacket(BYTE* InBuffer, int32 InBufferLength) abstract;

};

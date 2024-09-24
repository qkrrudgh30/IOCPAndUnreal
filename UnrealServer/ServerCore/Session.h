#pragma once

#include "IOCPCore.h"
#include "IOCPEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

struct USPacketHeader
{
    uint16 PacketSize; // Ư�� ��Ŷ�� �������� ������(�̸�, ���ڿ�, �ֺ���� �����鿡�� ��������ϴ� ������, ...)������ size �ʿ�.
    uint16 PacketID; // ��������ID (ex. 1=�α���, 2=�̵���û, ...)
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
    /* ���� ���� */
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

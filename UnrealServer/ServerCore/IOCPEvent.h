#pragma once

class USSession;

enum class EEventType : uint8
{
    Connect,
    Accept,
    Recv,
    Send,
    Disconnect,
};

class USIOCPEvent : public OVERLAPPED
{
public:
    USIOCPEvent(EEventType InEventType);

    void		Init();

public:
    EEventType	EventType;

    USIOCPObjectSharedPtr OwnerIOCPObject;

};

class USConnectEvent : public USIOCPEvent
{
public:
    USConnectEvent()
        : USIOCPEvent(EEventType::Connect)
    {
    }
};

class USAcceptEvent : public USIOCPEvent
{
public:
    USAcceptEvent()
        : USIOCPEvent(EEventType::Accept)
    {
    }

public:
    USSessionSharedPtr Session = nullptr;

};

class USRecvEvent : public USIOCPEvent
{
public:
    USRecvEvent() 
        : USIOCPEvent(EEventType::Recv) 
    { 
    }
};

class USSendEvent : public USIOCPEvent
{
public:
    USSendEvent()
        : USIOCPEvent(EEventType::Send) 
    {
    }

public:
    vector<USSendBufferSharedPtr> SendBuffers;

};

class USDisconnectEvent : public USIOCPEvent
{
public:
    USDisconnectEvent() 
        : USIOCPEvent(EEventType::Send)
    {
    }

};


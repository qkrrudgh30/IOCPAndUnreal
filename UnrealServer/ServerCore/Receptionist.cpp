#include "pch.h"
#include "Receptionist.h"
#include "SocketUtils.h"
#include "IOCPEvent.h"
#include "Session.h"
#include "Service.h"

USReceptionist::~USReceptionist()
{
    USSocketUtils::Close(ReceptionistSocket);

    for (USAcceptEvent* AcceptEvent : AcceptEvents)
    {
        //@TODO: 

        delete(AcceptEvent);
    }
}

bool USReceptionist::StartAccept(USServerServiceSharedPtr InServerService)
{
    ServerService = InServerService;
    if (ServerService == nullptr)
    {
        return false;
    }

    ReceptionistSocket = USSocketUtils::CreateSocket();
    if (ReceptionistSocket == INVALID_SOCKET)
    {
        return false;
    } 

    if (ServerService->GetIOCPCore()->Register(shared_from_this()) == false)
    {
        return false;
    }

    if (USSocketUtils::SetReuseAddress(ReceptionistSocket, true) == false)
    {
        return false;
    }

    if (USSocketUtils::SetLinger(ReceptionistSocket, 0, 0) == false)
    {
        return false;
    }

    if (USSocketUtils::Bind(ReceptionistSocket, ServerService->GetNetAddress()) == false)
    {
        return false;
    }

    if (USSocketUtils::Listen(ReceptionistSocket) == false)
    {
        return false;
    }

    const int32 AcceptCount = ServerService->GetMaxSessionCount();
    for (int32 i = 0; i < AcceptCount; i++)
    {
        USAcceptEvent* AcceptEvent = new USAcceptEvent();
        AcceptEvent->OwnerIOCPObject = shared_from_this();
        AcceptEvents.push_back(AcceptEvent);
        RegisterAccept(AcceptEvent);
    }

    return true;
}

void USReceptionist::CloseSocket()
{
    USSocketUtils::Close(ReceptionistSocket);
}

HANDLE USReceptionist::GetHandle()
{
    return reinterpret_cast<HANDLE>(ReceptionistSocket);
}

void USReceptionist::Dispatch(USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes)
{
    ASSERT_CRASH(InIOCPEvent->EventType == EEventType::Accept);
    USAcceptEvent* AcceptEvent = static_cast<USAcceptEvent*>(InIOCPEvent);
    ProcessAccept(AcceptEvent);
}

void USReceptionist::ProcessAccept(USAcceptEvent* InAcceptEvent)
{
    USSessionSharedPtr Session = InAcceptEvent->Session;

    if (false == USSocketUtils::SetUpdateAcceptSocket(Session->GetClientHandlerSocket(), ReceptionistSocket))
    {
        RegisterAccept(InAcceptEvent);
        return;
    }

    SOCKADDR_IN sockAddress;
    int32 sizeOfSockAddr = sizeof(sockAddress);
    if (SOCKET_ERROR == ::getpeername(Session->GetClientHandlerSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeOfSockAddr))
    {
        RegisterAccept(InAcceptEvent);
        return;
    }

    Session->SetClientAddress(USNetAddress(sockAddress));
    Session->ProcessConnect();
    RegisterAccept(InAcceptEvent);
}

void USReceptionist::RegisterAccept(USAcceptEvent* InAcceptEvent)
{
    USSessionSharedPtr Session = ServerService->CreateSession(); // Register IOCP

    InAcceptEvent->Init();
    InAcceptEvent->Session = Session;

    DWORD bytesReceived = 0;
    if (false == USSocketUtils::AcceptEx(ReceptionistSocket, Session->GetClientHandlerSocket(), Session->RecvBuffer.WriteFromCurrentPosition(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, OUT & bytesReceived, static_cast<LPOVERLAPPED>(InAcceptEvent)))
    {
        const int32 errorCode = ::WSAGetLastError();
        if (errorCode != WSA_IO_PENDING)
        {
            RegisterAccept(InAcceptEvent);
        }
    }
}

#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "Receptionist.h"

USService::USService(EServiceType InServiceType, USNetAddress InNetAddress, USIOCPCoreSharedPtr InIOCPCore, USSessionFactory InSessionFactory, int32 InMaxSessionCount)
    : ServiceType(InServiceType)
    , NetAddress(InNetAddress)
    , IOCPCore(InIOCPCore)
    , SessionFactory(InSessionFactory)
    , MaxSessionCount(InMaxSessionCount)
{

}

USService::~USService()
{
}

void USService::CloseService()
{
}

USSessionSharedPtr USService::CreateSession()
{
    USSessionSharedPtr Session = SessionFactory();
    Session->SetService(shared_from_this());

    if (IOCPCore->Register(Session) == false)
    {
        return nullptr;
    }

    return Session;
}

void USService::AddSession(USSessionSharedPtr InSession)
{
    WRITE_LOCK;
    ++SessionCount;
    Sessions.insert(InSession);
}

void USService::ReleaseSession(USSessionSharedPtr InSession)
{
    WRITE_LOCK;
    ASSERT_CRASH(Sessions.erase(InSession) != 0);
    --SessionCount;
}

void USService::Broadcast(USSendBufferSharedPtr InSendBuffer)
{
    WRITE_LOCK;
    for (const auto& Session : Sessions)
    {
        Session->Send(InSendBuffer);
    }
}

USClientService::USClientService(USNetAddress InServerAddress, USIOCPCoreSharedPtr InIOCPCore, USSessionFactory InSessionFactory, int32 InMaxSessionCount)
    : USService(EServiceType::Client, InServerAddress, InIOCPCore, InSessionFactory, InMaxSessionCount)
{
}

bool USClientService::Start()
{
    if (CanStart() == false)
    {
        return false;
    }

    const int32 MaxSessionCount = GetMaxSessionCount();
    for (int32 i = 0; i < MaxSessionCount; i++)
    {
        USSessionSharedPtr Session = CreateSession();
        if (Session->Connect() == false)
            return false;
    }

    return true;
}

USServerService::USServerService(USNetAddress InMyAddress, USIOCPCoreSharedPtr InIOCPCore, USSessionFactory InSessionFactory, int32 InMaxSessionCount)
    : USService(EServiceType::Server, InMyAddress, InIOCPCore, InSessionFactory, InMaxSessionCount)
{
}

bool USServerService::Start()
{
    if (CanStart() == false)
    {
        return false;
    }

    Receptionist = make_shared<USReceptionist>();
    if (Receptionist == nullptr)
    {
        return false;
    }

    USServerServiceSharedPtr ServerService = static_pointer_cast<USServerService>(shared_from_this());
    // ServerService의 부모 클래스인 Service 클래스에다가 enable_shared_from_this를 걸어줬기 때문에, shared_from_this()의 반환값은 Service 자료형임.
    if (Receptionist->StartAccept(ServerService) == false)
    {
        return false;
    }

    return true;
}

void USServerService::CloseService()
{
    // TODO

    USService::CloseService();
}

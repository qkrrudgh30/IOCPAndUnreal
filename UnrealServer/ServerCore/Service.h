#pragma once

#include <functional>

enum class EServiceType : uint8
{
    Server,
    Client
};

using USSessionFactory = function<USSessionSharedPtr(void)>;

class USService : public enable_shared_from_this<USService>
{
public:
    USService(EServiceType InServiceType, USNetAddress InNetAddress, USIOCPCoreSharedPtr InIOCPCore,
        USSessionFactory InSessionFactory, int32 InMaxSessionCount = 1);

    virtual ~USService();

    virtual bool Start() abstract;
    bool CanStart() { return SessionFactory != nullptr; }

    virtual void CloseService();
    void SetSessionFactory(USSessionFactory InSessionFactory) { SessionFactory = InSessionFactory; }

    USSessionSharedPtr CreateSession();
    void AddSession(USSessionSharedPtr InSession);
    void ReleaseSession(USSessionSharedPtr InSession);
    int32 GetCurrentSessionCount() { return SessionCount; }
    int32 GetMaxSessionCount() { return MaxSessionCount; }

    void Broadcast(USSendBufferSharedPtr InSendBuffer);

public:
    EServiceType GetServiceType() { return ServiceType; }
    USNetAddress GetNetAddress() { return NetAddress; }
    USIOCPCoreSharedPtr& GetIOCPCore() { return IOCPCore; }

protected:
    USE_LOCK;
    EServiceType ServiceType;
    USNetAddress NetAddress = {};
    USIOCPCoreSharedPtr IOCPCore;

    set<USSessionSharedPtr> Sessions;
    int32 SessionCount = 0;
    int32 MaxSessionCount = 0;
    USSessionFactory SessionFactory;

};

class USClientService : public USService
{
public:
    USClientService(USNetAddress InServerAddress, USIOCPCoreSharedPtr InIOCPCore, USSessionFactory InSessionFactory, int32 InMaxSessionCount = 1);

    virtual ~USClientService() {}

    virtual bool Start() override;
};

class USServerService : public USService
{
public:
    USServerService(USNetAddress InMyAddress, USIOCPCoreSharedPtr InIOCPCore, USSessionFactory InSessionFactory, int32 InMaxSessionCount = 1);
    virtual ~USServerService() {}

    virtual bool Start() override;
    virtual void CloseService() override;

private:
    USReceptionistSharedPtr Receptionist = nullptr;

};

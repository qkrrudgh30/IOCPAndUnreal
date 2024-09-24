#pragma once

#include "IOCPCore.h"
#include "NetAddress.h"

class USAcceptEvent;
class USServerService;

class USReceptionist : public USIOCPObject
{
public:
    USReceptionist() = default;

    ~USReceptionist();

public:
    /* �ܺο��� ��� */
    bool StartAccept(USServerServiceSharedPtr InServerService);

    void CloseSocket();

public:
    /* �������̽� ���� */
    virtual HANDLE GetHandle() override;

    virtual void Dispatch(class USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes = 0) override;

private:
    /* ���� ���� */
    void ProcessAccept(USAcceptEvent* InAcceptEvent);

    void RegisterAccept(USAcceptEvent* InAcceptEvent);

protected:
    SOCKET ReceptionistSocket = INVALID_SOCKET;

    vector<USAcceptEvent*> AcceptEvents;

    USServerServiceSharedPtr ServerService;

};

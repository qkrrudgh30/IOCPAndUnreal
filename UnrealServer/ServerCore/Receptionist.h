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
    /* 외부에서 사용 */
    bool StartAccept(USServerServiceSharedPtr InServerService);

    void CloseSocket();

public:
    /* 인터페이스 구현 */
    virtual HANDLE GetHandle() override;

    virtual void Dispatch(class USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes = 0) override;

private:
    /* 수신 관련 */
    void ProcessAccept(USAcceptEvent* InAcceptEvent);

    void RegisterAccept(USAcceptEvent* InAcceptEvent);

protected:
    SOCKET ReceptionistSocket = INVALID_SOCKET;

    vector<USAcceptEvent*> AcceptEvents;

    USServerServiceSharedPtr ServerService;

};

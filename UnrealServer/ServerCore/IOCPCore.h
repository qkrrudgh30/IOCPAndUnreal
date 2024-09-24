#pragma once

class USIOCPObject : public enable_shared_from_this<USIOCPObject>
{
public:
    virtual HANDLE GetHandle() abstract;

    virtual void Dispatch(class USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes = 0) abstract;

};

class USIOCPCore
{
public:
    USIOCPCore();

    ~USIOCPCore();

    HANDLE GetHandle() { return IOCPHandle; }

    bool Register(USIOCPObjectSharedPtr InIOCPObject);

    bool Dispatch(uint32 InTimeoutMS = INFINITE);

private:
    HANDLE		IOCPHandle;

};

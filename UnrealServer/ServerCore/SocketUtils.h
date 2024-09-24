#pragma once
#include "NetAddress.h"

class USSocketUtils
{
public:
    static void Init();

    static SOCKET CreateSocket();

    static bool BindWindowsFunction(SOCKET InSocket, GUID InGUID, LPVOID* InCallback);

    static bool SetLinger(SOCKET InSocket, uint16 InOnOff, uint16 InLinger);

    static bool SetReuseAddress(SOCKET InSocket, bool InFlag);

    static bool SetRecvBufferSize(SOCKET InSocket, int32 InSize);

    static bool SetSendBufferSize(SOCKET InSocket, int32 InSize);

    static bool SetTcpNoDelay(SOCKET InSocket, bool InFlag);

    static bool Bind(SOCKET InSocket, USNetAddress InNetAddress);

    static bool BindAnyAddress(SOCKET InSocket, uint16 InPortNumber);

    static bool Listen(SOCKET InReceptionistSocket, int32 InBackLog = SOMAXCONN);

    static bool SetUpdateAcceptSocket(SOCKET InClientHandlerSocket, SOCKET InReceptionistSocket);

    static void Close(SOCKET& InSocket);

    static void Clear();

public:
    static LPFN_CONNECTEX ConnectEx;

    static LPFN_DISCONNECTEX DisconnectEx;

    static LPFN_ACCEPTEX AcceptEx;

};

template<typename T>
static inline bool SetSockOpt(SOCKET InSocket, int32 InLevel, int32 InOptionName, T InOptionValue)
{
    return SOCKET_ERROR != ::setsockopt(InSocket, InLevel, InOptionName, reinterpret_cast<char*>(&InOptionValue), sizeof(T));
}


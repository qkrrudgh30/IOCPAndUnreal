#include "pch.h"
#include "SocketUtils.h"

LPFN_CONNECTEX USSocketUtils::ConnectEx = nullptr;
LPFN_DISCONNECTEX USSocketUtils::DisconnectEx = nullptr;
LPFN_ACCEPTEX USSocketUtils::AcceptEx = nullptr;

void USSocketUtils::Init()
{
	WSADATA WindowsSocketAPIData;
	ASSERT_CRASH(::WSAStartup(MAKEWORD(2, 2), OUT & WindowsSocketAPIData) == 0);

	SOCKET DummySocket = CreateSocket();
	ASSERT_CRASH(BindWindowsFunction(DummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx)));
	ASSERT_CRASH(BindWindowsFunction(DummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx)));
	ASSERT_CRASH(BindWindowsFunction(DummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisconnectEx)));

	Close(DummySocket);
}

SOCKET USSocketUtils::CreateSocket()
{
	return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

bool USSocketUtils::BindWindowsFunction(SOCKET InSocket, GUID InGUID, LPVOID* InCallback)
{
	DWORD Bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl(InSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &InGUID, sizeof(InGUID), InCallback, sizeof(*InCallback), OUT & Bytes, NULL, NULL);
}

bool USSocketUtils::SetLinger(SOCKET InSocket, uint16 InOnOff, uint16 InLinger)
{
	LINGER LingerOption;
	LingerOption.l_onoff = InOnOff;
	LingerOption.l_linger = InLinger;
	return SetSockOpt(InSocket, SOL_SOCKET, SO_LINGER, LingerOption);
}

bool USSocketUtils::SetReuseAddress(SOCKET InSocket, bool InFlag)
{
	return SetSockOpt(InSocket, SOL_SOCKET, SO_REUSEADDR, InFlag);
}

bool USSocketUtils::SetRecvBufferSize(SOCKET InSocket, int32 InSize)
{
	return SetSockOpt(InSocket, SOL_SOCKET, SO_RCVBUF, InSize);
}

bool USSocketUtils::SetSendBufferSize(SOCKET InSocket, int32 InSize)
{
	return SetSockOpt(InSocket, SOL_SOCKET, SO_SNDBUF, InSize);
}

bool USSocketUtils::SetTcpNoDelay(SOCKET InSocket, bool InFlag)
{
	return SetSockOpt(InSocket, SOL_SOCKET, TCP_NODELAY, InFlag);
}

bool USSocketUtils::Bind(SOCKET InSocket, USNetAddress InNetAddress)
{
	return SOCKET_ERROR != ::bind(InSocket, reinterpret_cast<const SOCKADDR*>(&InNetAddress.GetSocketAddress()), sizeof(SOCKADDR_IN));
}

bool USSocketUtils::BindAnyAddress(SOCKET InSocket, uint16 InPortNumber)
{
	SOCKADDR_IN MyAddress;
	MyAddress.sin_family = AF_INET;
	MyAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);
	MyAddress.sin_port = ::htons(InPortNumber);

	return SOCKET_ERROR != ::bind(InSocket, reinterpret_cast<const SOCKADDR*>(&MyAddress), sizeof(MyAddress));
}

bool USSocketUtils::Listen(SOCKET InReceptionistSocket, int32 InBackLog)
{
	return SOCKET_ERROR != ::listen(InReceptionistSocket, InBackLog);
}

bool USSocketUtils::SetUpdateAcceptSocket(SOCKET InClientHandlerSocket, SOCKET InReceptionistSocket)
{
	return SetSockOpt(InClientHandlerSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, InReceptionistSocket);
}

void USSocketUtils::Close(SOCKET& InSocket)
{
	if (InSocket != INVALID_SOCKET)
	{
		::closesocket(InSocket);
	}
	InSocket = INVALID_SOCKET;
}

void USSocketUtils::Clear()
{
	::WSACleanup();
}

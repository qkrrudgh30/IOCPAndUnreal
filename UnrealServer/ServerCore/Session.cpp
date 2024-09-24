#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SocketUtils.h"

USSession::USSession()
	: RecvBuffer(BUFFER_SIZE)
{
	ClientHandlerSocket = USSocketUtils::CreateSocket();
}

USSession::~USSession()
{
	USSocketUtils::Close(ClientHandlerSocket);
}

HANDLE USSession::GetHandle()
{
	return reinterpret_cast<HANDLE>(ClientHandlerSocket);
}

void USSession::Dispatch(USIOCPEvent* InIOCPEvent, int32 InNumberOfBytes)
{
	switch (InIOCPEvent->EventType)
	{
	case EEventType::Connect:
		ProcessConnect();
		break;
	case EEventType::Recv:
		ProcessRecv(InNumberOfBytes);
		break;
	case EEventType::Send:
		ProcessSend(InNumberOfBytes);
		break;
	case EEventType::Disconnect:
		ProcessDisconnect();
		break;
	default:
		break;
	}
}

void USSession::Disconnect(const WCHAR* InCause)
{
	if (IsClientConnected.exchange(false) == false)
		return;

	wcout << "Disconnect : " << InCause << endl;

	RegisterDisconnect();
}

bool USSession::RegisterConnect()
{
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != EServiceType::Client)
		return false;

	if (USSocketUtils::SetReuseAddress(ClientHandlerSocket, true) == false)
		return false;

	if (USSocketUtils::BindAnyAddress(ClientHandlerSocket, 0) == false)
		return false;

	ConnectEvent.Init();
	ConnectEvent.OwnerIOCPObject = shared_from_this(); // ADD_REF

	DWORD numOfBytes = 0;
	SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSocketAddress();
	if (false == USSocketUtils::ConnectEx(ClientHandlerSocket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, &ConnectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			ConnectEvent.OwnerIOCPObject = nullptr; // RELEASE_REF
			return false;
		}
	}

	return true;
}

void USSession::RegisterRecv()
{
	if (IsConnected() == false)
		return;

	RecvEvent.Init();
	RecvEvent.OwnerIOCPObject = shared_from_this();

	WSABUF WindowsSocketAPIBuffer;
	WindowsSocketAPIBuffer.buf = reinterpret_cast<char*>(RecvBuffer.WriteFromCurrentPosition());
	WindowsSocketAPIBuffer.len = RecvBuffer.GetFreeSizeToRead();

	DWORD NumberOfBytes = 0;
	DWORD Flags = 0;
	if (SOCKET_ERROR == ::WSARecv(ClientHandlerSocket, &WindowsSocketAPIBuffer, 1, OUT & NumberOfBytes, OUT & Flags, &RecvEvent, nullptr))
	{
		int32 ErrorCode = ::WSAGetLastError();
		if (ErrorCode != WSA_IO_PENDING)
		{
			HandleError(ErrorCode);
			RecvEvent.OwnerIOCPObject = nullptr;
		}
	}
}

void USSession::RegisterSend()
{
	if (IsConnected() == false)
		return;

	SendEvent.Init();
	SendEvent.OwnerIOCPObject = shared_from_this(); // ADD_REF

	{
		WRITE_LOCK;

		int32 WriteSize = 0;
		while (SendBufferQueue.empty() == false)
		{
			USSendBufferSharedPtr SendBuffer = SendBufferQueue.front();

			WriteSize += SendBuffer->GetWriteSize();

			SendBufferQueue.pop();
			SendEvent.SendBuffers.push_back(SendBuffer);
		}
	}

	vector<WSABUF> wsaBufs;
	wsaBufs.reserve(SendEvent.SendBuffers.size());
	for (USSendBufferSharedPtr SendBuffer : SendEvent.SendBuffers)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(SendBuffer->GetBuffer());
		wsaBuf.len = static_cast<LONG>(SendBuffer->GetWriteSize());
		wsaBufs.push_back(wsaBuf);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(ClientHandlerSocket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT & numOfBytes, 0, &SendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			SendEvent.OwnerIOCPObject = nullptr;
			SendEvent.SendBuffers.clear();
			bIsSendBufferRegistered.store(false);
		}
	}
}

bool USSession::RegisterDisconnect()
{
	DisconnectEvent.Init();
	DisconnectEvent.OwnerIOCPObject = shared_from_this(); // ADD_REF

	if (false == USSocketUtils::DisconnectEx(ClientHandlerSocket, &DisconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 ErrorCode = ::WSAGetLastError();
		if (ErrorCode != WSA_IO_PENDING)
		{
			DisconnectEvent.OwnerIOCPObject = nullptr; // RELEASE_REF
			return false;
		}
	}

	return true;
}

void USSession::ProcessConnect()
{
	ConnectEvent.OwnerIOCPObject = nullptr; // RELEASE_REF

	IsClientConnected.store(true);

	shared_ptr<USService> Service = GetService();
	Service->AddSession(GetSessionRef());

	OnConnected();

	RegisterRecv();
}

void USSession::ProcessRecv(int32 InNumberOfBytes)
{
	RecvEvent.OwnerIOCPObject = nullptr; // RELEASE_REF

	if (InNumberOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	if (RecvBuffer.OnWrite(InNumberOfBytes) == false)
	{
		Disconnect(L"OnWrite Overflow");
		return;
	}

	int32 DataSize = RecvBuffer.GetRemainingReadDataSize();
	int32 ProcessLen = OnRecv(RecvBuffer.ReadFromCurrentPosition(), DataSize);
	if (ProcessLen < 0 || DataSize < ProcessLen || RecvBuffer.OnRead(ProcessLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	cout << "Recv Data Len = " << InNumberOfBytes << endl;

	//OnRecv(RecvBuffer, InNumberOfBytes);
	RecvBuffer.Clean();

	RegisterRecv();
}

void USSession::ProcessSend(int32 InNumberOfBytes)
{
	//InSendEvent->OwnerIOCPObject = nullptr; // RELEASE_REF
	SendEvent.OwnerIOCPObject = nullptr; // RELEASE_REF
	//xdelete(InSendEvent);
	SendEvent.SendBuffers.clear();

	if (InNumberOfBytes == 0)
	{
		Disconnect(L"Send 0");
		return;
	}

	OnSend(InNumberOfBytes);

	WRITE_LOCK;
	if (SendBufferQueue.empty())
		bIsSendBufferRegistered.store(false);
	else
		RegisterSend();
}

void USSession::ProcessDisconnect()
{
	DisconnectEvent.OwnerIOCPObject = nullptr; // RELEASE_REF

	OnDisconnected(); // 컨텐츠 코드에서 재정의
	GetService()->ReleaseSession(GetSessionRef());
}

void USSession::HandleError(int32 InErrorCode)
{
	switch (InErrorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		Disconnect(L"HandleError");
		break;
	default:
		// TODO : Log
		cout << "Handle Error : " << InErrorCode << endl;
		break;
	}
}

void USSession::Send(USSendBufferSharedPtr InSendBuffer)
{
	if (IsConnected() == false)
	{
		return;
	}

	bool bIsSendPermissionAccquired = false;

	{
		WRITE_LOCK;
		SendBufferQueue.push(InSendBuffer);

		if (bIsSendBufferRegistered.exchange(true) == false)
		{
			bIsSendPermissionAccquired = true;
		}
	}

	if (bIsSendPermissionAccquired == true)
		RegisterSend();
}

bool USSession::Connect()
{
	return RegisterConnect();
}

USPacketSession::USPacketSession()
{
}

USPacketSession::~USPacketSession()
{
}

int32 USPacketSession::OnRecv(BYTE* InBuffer, int32 InBufferLength)
{
	int32 CurrentProcessedBufferLength = 0;

	while (true)
	{
		int32 BufferLengthToProcess = InBufferLength - CurrentProcessedBufferLength;
		// 최소한 헤더(지금은 size와 id부분)는 파싱할 수 있어야 한다
		if (BufferLengthToProcess < sizeof(USPacketHeader))
			break;

		USPacketHeader PacketHeader = *(reinterpret_cast<USPacketHeader*>(&InBuffer[CurrentProcessedBufferLength]));
		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if (BufferLengthToProcess < PacketHeader.PacketSize)
			break;

		// 패킷 조립 성공
		OnRecvPacket(&InBuffer[CurrentProcessedBufferLength], PacketHeader.PacketSize);

		CurrentProcessedBufferLength += PacketHeader.PacketSize;
	}

	return CurrentProcessedBufferLength;
}

#include "pch.h"


USIOCPCore::USIOCPCore()
{
	IOCPHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(IOCPHandle != INVALID_HANDLE_VALUE);
}

USIOCPCore::~USIOCPCore()
{
	::CloseHandle(IOCPHandle);
}

bool USIOCPCore::Register(USIOCPObjectSharedPtr InIOCPObject)
{
	return ::CreateIoCompletionPort(InIOCPObject->GetHandle(), IOCPHandle, /*key*/0, 0);
}

bool USIOCPCore::Dispatch(uint32 InTimeoutMS)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	USIOCPEvent* IOCPEvent = nullptr;

	if (::GetQueuedCompletionStatus(IOCPHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&IOCPEvent), InTimeoutMS))
	{
		USIOCPObjectSharedPtr IOCPObject = IOCPEvent->OwnerIOCPObject;
		IOCPObject->Dispatch(IOCPEvent, numOfBytes);
	}
	else
	{
		int32 ErrorCode = ::WSAGetLastError();
		switch (ErrorCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			USIOCPObjectSharedPtr IOCPObject = IOCPEvent->OwnerIOCPObject;
			IOCPObject->Dispatch(IOCPEvent, numOfBytes);
			break;
		}
	}

	return true;
}

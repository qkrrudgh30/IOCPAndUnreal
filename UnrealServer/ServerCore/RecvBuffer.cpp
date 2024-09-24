#include "pch.h"
#include "RecvBuffer.h"

USRecvBuffer::USRecvBuffer(int32 InRecvBufferSize)
	: RecvBufferSize(InRecvBufferSize)
{
	RecvBufferCapacity = RecvBufferSize * BUFFER_COUNT;
	Buffer.resize(RecvBufferCapacity);
}

USRecvBuffer::~USRecvBuffer()
{
}

void USRecvBuffer::Clean()
{
	int32 RemainingReadDataSize = GetRemainingReadDataSize();
	if (RemainingReadDataSize == 0)
	{
		// 딱 마침 읽기+쓰기 커서가 동일한 위치라면, 둘 다 리셋.
		CurrentReadPosition = CurrentWritePosition = 0;
	}
	else
	{
		// 여유 공간이 버퍼 1개 크기 미만이면, 데이터를 앞으로 땅긴다.
		if (GetFreeSizeToRead() < RecvBufferSize)
		{
			::memcpy(&Buffer[0], &Buffer[CurrentReadPosition], RemainingReadDataSize);
			CurrentReadPosition = 0;
			CurrentWritePosition = RemainingReadDataSize;
		}
	}
}

bool USRecvBuffer::OnRead(int32 InNumberOfBytes)
{
	if (GetRemainingReadDataSize() < InNumberOfBytes)
		return false;

	CurrentReadPosition += InNumberOfBytes;
	return true;
}

bool USRecvBuffer::OnWrite(int32 InNumberOfBytes)
{
	if (GetFreeSizeToRead() < InNumberOfBytes)
		return false;

	CurrentWritePosition += InNumberOfBytes;
	return true;
}

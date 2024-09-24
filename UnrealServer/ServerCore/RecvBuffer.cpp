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
		// �� ��ħ �б�+���� Ŀ���� ������ ��ġ���, �� �� ����.
		CurrentReadPosition = CurrentWritePosition = 0;
	}
	else
	{
		// ���� ������ ���� 1�� ũ�� �̸��̸�, �����͸� ������ �����.
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

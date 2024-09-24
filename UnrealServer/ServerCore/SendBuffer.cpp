#include "pch.h"
#include "SendBuffer.h"

USSendBuffer::USSendBuffer(int32 InBufferSize)
{
	Buffer.resize(InBufferSize);
}

USSendBuffer::~USSendBuffer()
{
}

void USSendBuffer::CopyData(void* InData, int32 InLength)
{
	ASSERT_CRASH(static_cast<uint32>(InLength) <= GetCapacity());
	::memcpy(Buffer.data(), InData, InLength);
	WriteSize = InLength;
}

void USSendBuffer::Close(uint32 InWriteSize)
{
	WriteSize = InWriteSize;
}

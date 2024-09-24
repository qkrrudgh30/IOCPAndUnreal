#include "pch.h"
#include "ReadableBuffer.h"

USReadableBuffer::USReadableBuffer()
{
}

USReadableBuffer::USReadableBuffer(BYTE* InBuffer, uint32 InBufferSize, uint32 CurrentReadPosition)
	: Buffer(InBuffer), BufferSize(InBufferSize), CurrentReadPosition(CurrentReadPosition)
{

}

USReadableBuffer::~USReadableBuffer()
{
}

bool USReadableBuffer::Peek(void* InStartPtrToRead, uint32 InReadLength)
{
    if (GetFreeSize() < InReadLength)
        return false;

    ::memcpy(InStartPtrToRead, &Buffer[CurrentReadPosition], InReadLength);
    return true;
}

bool USReadableBuffer::Read(void* InStartPtrToRead, uint32 InReadLength)
{
    if (Peek(InStartPtrToRead, InReadLength) == false)
        return false;

    CurrentReadPosition += InReadLength;
    return true;
}

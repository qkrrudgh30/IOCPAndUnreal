#include "WritableBuffer.h"

USWritableBuffer::USWritableBuffer()
{
}

USWritableBuffer::USWritableBuffer(BYTE* InBuffer, uint32 InBufferSize, uint32 InCurrentWritePosition)
	: Buffer(InBuffer), BufferSize(InBufferSize), CurrentWritePosition(InCurrentWritePosition)
{

}

USWritableBuffer::~USWritableBuffer()
{
}

bool USWritableBuffer::Write(void* InStartPtrToWrite, uint32 InWriteLength)
{
    if (GetFreeSize() < InWriteLength)
        return false;

    ::memcpy(&Buffer[CurrentWritePosition], InStartPtrToWrite, InWriteLength);
    CurrentWritePosition += InWriteLength;
    return true;
}

#pragma once

class USReadableBuffer
{
public:
    USReadableBuffer();
    USReadableBuffer(BYTE* InBuffer, uint32 InBufferSize, uint32 CurrentReadPosition = 0);
    ~USReadableBuffer();

    BYTE* GetBuffer() { return Buffer; }
    uint32 GetBufferSize() { return BufferSize; }
    uint32 GetCurrentReadPosition() { return CurrentReadPosition; }
    uint32 GetFreeSize() { return BufferSize - CurrentReadPosition; }

    template<typename T>
    bool Peek(T* InStartPtrToRead) { return Peek(InStartPtrToRead, sizeof(T)); }
    bool Peek(void* InStartPtrToRead, uint32 InReadLength);

    template<typename T>
    bool Read(T* InStartPtrToRead) { return Read(InStartPtrToRead, sizeof(T)); }
    bool Read(void* InStartPtrToRead, uint32 InReadLength);

    template<typename T>
    USReadableBuffer& operator>>(OUT T& InStartPtrToRead);

private:
    BYTE* Buffer = nullptr;
    
    uint32 BufferSize = 0;
    
    uint32 CurrentReadPosition = 0;
    
};

template<typename T>
inline USReadableBuffer& USReadableBuffer::operator>>(OUT T& InStartPtrToRead)
{
    InStartPtrToRead = *reinterpret_cast<T*>(&Buffer[CurrentReadPosition]);
    CurrentReadPosition += sizeof(T);
    return *this;
}

#pragma once

class USWritableBuffer
{
public:
    USWritableBuffer();
    USWritableBuffer(BYTE* InBuffer, uint32 InBufferSize, uint32 InCurrentWritePosition = 0);
    ~USWritableBuffer();

    BYTE* GetBuffer() { return Buffer; }
    uint32 GetBufferSize() { return BufferSize; }
    uint32 GetCurrentWritePosition() { return CurrentWritePosition; }
    uint32 GetFreeSize() { return BufferSize - CurrentWritePosition; }

    template<typename T>
    bool Write(T* InStartPtrToWrite) { return Write(InStartPtrToWrite, sizeof(T)); }
    bool Write(void* InStartPtrToWrite, uint32 InWriteLength);

    template<typename T>
    T* Reserve(uint16 InCount = 1);

    template<typename T>
    USWritableBuffer& operator<<(T&& InStartPtrToWrite);

private:
    BYTE* Buffer = nullptr;

    uint32 BufferSize = 0;
    
    uint32 CurrentWritePosition = 0;
    
};

template<typename T>
T* USWritableBuffer::Reserve(uint16 InCount)
{
    if (GetFreeSize() < (sizeof(T) * InCount))
        return nullptr;

    T* ret = reinterpret_cast<T*>(&Buffer[CurrentWritePosition]);
    CurrentWritePosition += (sizeof(T) * InCount);
    return ret;
}

template<typename T>
USWritableBuffer& USWritableBuffer::operator<<(T&& InStartPtrToWrite)
{
    using DataType = std::remove_reference_t<T>;
    *reinterpret_cast<DataType*>(&Buffer[CurrentWritePosition]) = std::forward<DataType>(InStartPtrToWrite);
    CurrentWritePosition += sizeof(T);
    return *this;
}

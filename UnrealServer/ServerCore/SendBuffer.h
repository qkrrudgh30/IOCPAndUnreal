#pragma once

class USSendBuffer
{
public:
	USSendBuffer(int32 InBufferSize);
	~USSendBuffer();

	BYTE* GetBuffer() { return Buffer.data(); }
	uint32 GetWriteSize() { return WriteSize; }
	uint32 GetCapacity() { return static_cast<int32>(Buffer.size()); }

	void CopyData(void* InData, int32 InLength);
	void Close(uint32 InWriteSize);

private:
	vector<BYTE> Buffer;
	uint32       WriteSize = 0;

};


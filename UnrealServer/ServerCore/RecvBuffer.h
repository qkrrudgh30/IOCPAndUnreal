#pragma once
class USRecvBuffer
{
	enum { BUFFER_COUNT = 10 };

public:
	USRecvBuffer(int32 InRecvBufferSize);
	~USRecvBuffer();

	void			Clean();
	bool			OnRead(int32 InNumberOfBytes);
	bool			OnWrite(int32 InNumberOfBytes);

	BYTE*           ReadFromCurrentPosition() { return &Buffer[CurrentReadPosition]; }
	BYTE*           WriteFromCurrentPosition() { return &Buffer[CurrentWritePosition]; }
	int32			GetRemainingReadDataSize() { return CurrentWritePosition - CurrentReadPosition; }
	int32			GetFreeSizeToRead() { return RecvBufferCapacity - CurrentWritePosition; }

private:
	int32			RecvBufferCapacity = 0;
	int32			RecvBufferSize = 0;
	int32			CurrentReadPosition = 0;
	int32			CurrentWritePosition = 0;
	vector<BYTE>	Buffer;
};

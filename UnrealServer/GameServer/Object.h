#pragma once

class USRoom;

class USObject : public enable_shared_from_this<USObject>
{
public:
	USObject();
	virtual ~USObject();

	bool IsPlayer() { return bIsPlayer; }

public:
	Protocol::ObjectInfo* ObjectInfo;
	Protocol::PosInfo* PosInfo;

public:
	atomic<weak_ptr<USRoom>> Room;

protected:
	bool bIsPlayer = false;

};


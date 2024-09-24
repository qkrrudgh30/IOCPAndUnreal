#pragma once

class USObjectManager
{
public:
	static USPlayerCharacterSharedPtr CreatePlayer(USClientSessionSharedPtr InClientSession);

private:
	static atomic<int64> IDGenerator;

};


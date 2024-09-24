#include "pch.h"
#include "CoreGlobal.h"

USThreadManager* GThreadManager = nullptr;

USGlobalQueue* GGlobalQueue = nullptr;

USJobTimer* GJobTimer = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new USThreadManager();
		
		GGlobalQueue = new USGlobalQueue();
		
		GJobTimer = new USJobTimer();

		USSocketUtils::Init();
	}

	~CoreGlobal()
	{
		delete GThreadManager;
		GThreadManager = nullptr;

		delete GGlobalQueue;
		GGlobalQueue = nullptr;

		delete GJobTimer;
		GJobTimer = nullptr;

		USSocketUtils::Clear();
	}

} GCoreGlobal;

#include <iostream>

#include "pch.h"
#include "ThreadManager.h"
#include "Room.h"
#include "ClientSessionManager.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(USServerServiceSharedPtr& InServerService)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
		InServerService->GetIOCPCore()->Dispatch(10);

		// 예약된 일감 처리
		USThreadManager::DistributeReservedJobs();

		// 글로벌 큐
		USThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	USServerPacketHandler::Init();

	USServerServiceSharedPtr service = make_shared<USServerService>(
		USNetAddress(L"127.0.0.1", 8888),
		make_shared<USIOCPCore>(),
		[=]() { return make_shared<USClientSession>(); },
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
			{
				DoWorkerJob(service);
			});
	}

	// Main Thread
	//DoWorkerJob(service);

	GRoom->DoAsync(&USRoom::UpdateTick);

	while (true)
	{
		Protocol::S_CHAT pkt;
		pkt.set_msg("HelloWorld");
		auto sendBuffer = USServerPacketHandler::MakePacket(pkt);

		GClientSessionManager.Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}

	GThreadManager->Join();
}

#include "pch.h"
#include "ThreadManager.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "GlobalQueue.h"

USThreadManager::USThreadManager()
{
    InitTLS();
}

USThreadManager::~USThreadManager()
{
    Join();
}

void USThreadManager::Launch(function<void(void)> InCallback)
{
    lock_guard LockGuard(Lock);

    Threads.push_back(thread([this, InCallback]() -> void
        {
            InitTLS();

            InCallback();

            DestroyTLS();
        }
    ));
}

void USThreadManager::Join()
{
    for (thread& t : Threads)
    {
        if (t.joinable() == true)
        {
            t.join();
        }
    }

    Threads.clear();
}

void USThreadManager::InitTLS()
{
    static atomic<uint32> ThreadID = 1;
    LThreadID = ThreadID.fetch_add(1);
}

void USThreadManager::DestroyTLS()
{
}

void USThreadManager::DoGlobalQueueWork()
{
    while (true)
    {
        uint64 Now = ::GetTickCount64();
        if (LEndTickCount < Now)
        {
            break;
        }

        USJobQueueSharedPtr JobQueue = GGlobalQueue->Pop();
        if (JobQueue == nullptr)
            break;

        JobQueue->Execute();
    }
}

void USThreadManager::DistributeReservedJobs()
{
    const uint64 Now = ::GetTickCount64();

    GJobTimer->Distribute(Now);
}

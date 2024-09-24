#pragma once

#include <thread>
#include <functional>

class USThreadManager
{
public:
    USThreadManager();
    ~USThreadManager();

    void Launch(function<void(void)> InCallback);
    void Join();

    static void InitTLS();
    static void DestroyTLS();

    static void DoGlobalQueueWork();
    static void DistributeReservedJobs();

private:
    mutex          Lock;
    vector<thread> Threads;

};


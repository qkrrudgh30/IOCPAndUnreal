#include "pch.h"
#include "JobQueue.h"

void USJobQueue::Push(USJobSharedPtr InJob, bool InIsPushOnly)
{
	const int32 PreviousJobCount = JobCount.fetch_add(1);
	JobQueue.Push(InJob);

	if (PreviousJobCount == 0)
	{
		if (LCurrentJobQueue == nullptr && InIsPushOnly == false)
		{
			Execute();
		}
		else
		{
			GGlobalQueue->Push(shared_from_this());
		}
	}
}

void USJobQueue::Execute()
{
	LCurrentJobQueue = this;

	while (true)
	{
		vector<USJobSharedPtr> Jobs;
		JobQueue.PopAll(OUT Jobs);

		const int32 JobCountToProcess = static_cast<int32>(Jobs.size());
		for (int32 i = 0; i < JobCountToProcess; i++)
			Jobs[i]->Execute();

		if (JobCount.fetch_sub(JobCountToProcess) == JobCountToProcess)
		{
			LCurrentJobQueue = nullptr;
			return;
		}

		const uint64 Now = ::GetTickCount64();
		if (LEndTickCount <= Now)
		{
			LCurrentJobQueue = nullptr;
			GGlobalQueue->Push(shared_from_this());
			break;
		}
	}
}


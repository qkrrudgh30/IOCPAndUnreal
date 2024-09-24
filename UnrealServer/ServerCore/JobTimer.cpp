#include "pch.h"


void USJobTimer::Reserve(uint64 InTickAfter, weak_ptr<USJobQueue> InOwnerJobQueue, USJobSharedPtr InJob)
{
	const uint64 ExecuteTick = ::GetTickCount64() + InTickAfter;
	USJobData* JobData = new USJobData(InOwnerJobQueue, InJob);

	WRITE_LOCK;

	Entries.push(USTimerEntry{ ExecuteTick, JobData });
}

void USJobTimer::Distribute(uint64 InNow)
{
	// 한 번에 1 쓰레드만 통과. 근데 아래서 Lock 잡는데, 왜 굳이 1스레드만?
	// 정말 간발의 차로, 첫 스레드가 하나 꺼내서 실행하는 그 와중에
	// 두 번째 스레드가 들어와서 두개를 꺼내서 실행할 수 도 있음. 그럼 첫스레드는 낙동강 오리알 행. 극악의 확률로 발생하는 버그. 근데 발생하면 찾기 엄청 어려움.
	if (bIsDistributing.exchange(true) == true)
		return;

	vector<USTimerEntry> EntriesToDistribute;

	{
		WRITE_LOCK;

		while (Entries.empty() == false)
		{
			const USTimerEntry& TimerEntry = Entries.top();
			if (InNow < TimerEntry.ExecuteTick)
				break;

			EntriesToDistribute.push_back(TimerEntry);
			Entries.pop();
		}
	}

	for (USTimerEntry& ItemToDistribute : EntriesToDistribute)
	{
		if (USJobQueueSharedPtr JobQueue = ItemToDistribute.JobData->OwnerJobQueue.lock())
			JobQueue->Push(ItemToDistribute.JobData->Job);

		delete ItemToDistribute.JobData;
	}

	// 끝났으면 풀어준다
	bIsDistributing.store(false);
}

void USJobTimer::Clear()
{
	WRITE_LOCK;

	while (Entries.empty() == false)
	{
		const USTimerEntry& timerItem = Entries.top();
		delete timerItem.JobData;
		Entries.pop();
	}
}

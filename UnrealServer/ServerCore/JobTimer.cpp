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
	// �� ���� 1 �����常 ���. �ٵ� �Ʒ��� Lock ��µ�, �� ���� 1�����常?
	// ���� ������ ����, ù �����尡 �ϳ� ������ �����ϴ� �� ���߿�
	// �� ��° �����尡 ���ͼ� �ΰ��� ������ ������ �� �� ����. �׷� ù������� ������ ������ ��. �ؾ��� Ȯ���� �߻��ϴ� ����. �ٵ� �߻��ϸ� ã�� ��û �����.
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

	// �������� Ǯ���ش�
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

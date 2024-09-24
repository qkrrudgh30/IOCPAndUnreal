#pragma once

struct USJobData
{
	USJobData(weak_ptr<USJobQueue> InOwnerJobQueue, USJobSharedPtr InJob)
		: OwnerJobQueue(InOwnerJobQueue)
		, Job(InJob)
	{

	}

	weak_ptr<USJobQueue> OwnerJobQueue;
	USJobSharedPtr       Job;

};

struct USTimerEntry
{
	bool operator<(const USTimerEntry& Other) const
	{
		return Other.ExecuteTick < ExecuteTick;
	}

	uint64     ExecuteTick = 0;
	USJobData* JobData = nullptr;

};

class USJobTimer
{
public:
	void Reserve(uint64 InTickAfter, weak_ptr<USJobQueue> InOwnerJobQueue, USJobSharedPtr InJob);
	void Distribute(uint64 InNow);
	void Clear();

private:
	USE_LOCK;
	priority_queue<USTimerEntry> Entries;
	atomic<bool>                 bIsDistributing = false;

};


#pragma once

class USGlobalQueue
{
public:
	USGlobalQueue();
	~USGlobalQueue();

	void                Push(USJobQueueSharedPtr InJobQueue);
	USJobQueueSharedPtr Pop();

private:
	USLockQueue<USJobQueueSharedPtr> JobQueues;

};

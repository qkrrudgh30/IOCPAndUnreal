#include "pch.h"
#include "GlobalQueue.h"

USGlobalQueue::USGlobalQueue()
{
}

USGlobalQueue::~USGlobalQueue()
{
}

void USGlobalQueue::Push(USJobQueueSharedPtr InJobQueue)
{
	JobQueues.Push(InJobQueue);
}

USJobQueueSharedPtr USGlobalQueue::Pop()
{
	return JobQueues.Pop();
}

#pragma once

#include "Job.h"
#include "LockQueue.h"
#include "JobTimer.h"

class USJobQueue : public enable_shared_from_this<USJobQueue>
{
public:
	void DoAsync(USCallbackFunctionType&& InCallbackFunction)
	{
		Push(make_shared<USJob>(std::move(InCallbackFunction)));
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::* InMemberFunction)(Args...), Args... InMemberFunctionArguments)
	{
		shared_ptr<T> OwnerJobQueue = static_pointer_cast<T>(shared_from_this());
		Push(make_shared<USJob>(OwnerJobQueue, InMemberFunction, std::forward<Args>(InMemberFunctionArguments)...));
	}

	void ClearJobs() { JobQueue.Clear(); }

	void DoTimer(uint64 InTickAfter, USCallbackFunctionType&& InCallbackFunction)
	{
		USJobSharedPtr Job = make_shared<USJob>(std::move(InCallbackFunction));
		GJobTimer->Reserve(InTickAfter, shared_from_this(), Job);
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(uint64 InTickAfter, Ret(T::* InMemberFunction)(Args...), Args... InMemberFunctionArguments)
	{
		shared_ptr<T> OwnerJobQueue = static_pointer_cast<T>(shared_from_this());
		USJobSharedPtr Job = make_shared<USJob>(OwnerJobQueue, InMemberFunction, std::forward<Args>(InMemberFunctionArguments)...);
		GJobTimer->Reserve(InTickAfter, shared_from_this(), Job);
	}

public:
	void Execute();
	void Push(USJobSharedPtr InJob, bool InIsPushOnly = false);

protected:
	USLockQueue<USJobSharedPtr> JobQueue;
	atomic<int32>               JobCount = 0;

};


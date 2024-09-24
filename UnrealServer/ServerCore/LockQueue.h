#pragma once

template<typename T>
class USLockQueue
{
public:
	void Push(T InItem)
	{
		WRITE_LOCK;
		Queue.push(InItem);
	}

	T Pop()
	{
		WRITE_LOCK;
		return PopWithoutLock();
	}

	T PopWithoutLock()
	{
		if (Queue.empty() == true)
		{
			return T();
		}

		T ReturnedItem = Queue.front();
		Queue.pop();
		return ReturnedItem;
	}

	void PopAll(OUT vector<T>& Items)
	{
		WRITE_LOCK;
		while (T Item = PopWithoutLock())
			Items.push_back(Item);
	}

	void Clear()
	{
		WRITE_LOCK;
		Queue = queue<T>();
	}

private:
	USE_LOCK;
	queue<T> Queue;

};


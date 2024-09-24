#pragma once
#include <functional>

using USCallbackFunctionType = std::function<void()>;

class USJob
{
public:
	USJob(USCallbackFunctionType&& InCallbackFunction)
		: CallbackFunction(std::move(InCallbackFunction))
	{
	}

	template<typename T, typename Ret, typename... Args>
	USJob(shared_ptr<T> InOwner, Ret(T::* InMemberFunction)(Args...), Args&&... InMemberFunctionArguments)
	{
		CallbackFunction = [InOwner, InMemberFunction, InMemberFunctionArguments...]()
			{
				(InOwner.get()->*InMemberFunction)(InMemberFunctionArguments...);
			};
	}

	void Execute()
	{
		CallbackFunction();
	}

private:
	USCallbackFunctionType CallbackFunction;

};


#pragma once

#define OUT

#define NAMESPACE_BEGIN(name)	namespace name {
#define NAMESPACE_END			}

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}

#define USE_MANY_LOCKS(InCount) mutex Locks[InCount];
#define USE_LOCK                USE_MANY_LOCKS(1);
#define WRITE_LOCK_IDX(InIndex) lock_guard<mutex> LockGuard_##Index(Locks[InIndex])
#define WRITE_LOCK              WRITE_LOCK_IDX(0)

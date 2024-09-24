#include "pch.h"
#include "CoreTLS.h"

thread_local uint32            LThreadID = 0;

thread_local uint64            LEndTickCount = 0;

thread_local stack<int32>      LLockStack;

thread_local USJobQueue*       LCurrentJobQueue = nullptr;

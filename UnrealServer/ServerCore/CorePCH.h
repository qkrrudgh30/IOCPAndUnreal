#pragma once

#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

#include <windows.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "SocketUtils.h"
#include "JobTimer.h"
#include "LockQueue.h"
#include "GlobalQueue.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "ReadableBuffer.h"
#include "WritableBuffer.h"
#include "JobQueue.h"
#include "Service.h"

#include "Job.h"
#include "JobTimer.h"
#include "JobQueue.h"

#include "IOCPCore.h"
#include "IOCPEvent.h"

#include "Session.h"


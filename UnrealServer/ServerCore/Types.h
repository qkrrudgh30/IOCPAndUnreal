#pragma once

#include <mutex>
#include <atomic>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#define DEFINE_SHARED_PTR(InClassName) using InClassName##SharedPtr = std::shared_ptr<class InClassName>;

DEFINE_SHARED_PTR(USIOCPCore);
DEFINE_SHARED_PTR(USIOCPObject);
DEFINE_SHARED_PTR(USSession);
DEFINE_SHARED_PTR(USPacketSession);
DEFINE_SHARED_PTR(USReceptionist);
DEFINE_SHARED_PTR(USServerService);
DEFINE_SHARED_PTR(USClientService);
DEFINE_SHARED_PTR(USSendBuffer);
DEFINE_SHARED_PTR(USJob);
DEFINE_SHARED_PTR(USJobQueue);

#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))
#define len16(arr)		static_cast<int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)		static_cast<int32>(sizeof(arr)/sizeof(arr[0]))

#include "pch.h"
#include "IOCPEvent.h"

USIOCPEvent::USIOCPEvent(EEventType InEventType)
	: EventType(InEventType)
{
	Init();
}

void USIOCPEvent::Init()
{
    OVERLAPPED::hEvent = 0;
    OVERLAPPED::Internal = 0;
    OVERLAPPED::InternalHigh = 0;
    OVERLAPPED::Offset = 0;
    OVERLAPPED::OffsetHigh = 0;
}

#include "pch.h"
#include "NetAddress.h"

USNetAddress::USNetAddress(SOCKADDR_IN InSocketAddress)
     : SocketAddress(InSocketAddress)
{
}

USNetAddress::USNetAddress(wstring InIPString, uint16 InPortNumber)
{
    ::memset(&SocketAddress, 0, sizeof(SocketAddress));
    SocketAddress.sin_family = AF_INET;
    SocketAddress.sin_addr = IP2Address(InIPString.c_str());
    SocketAddress.sin_port = ::htons(InPortNumber);
}

wstring USNetAddress::GetIPAddressWString()
{
    WCHAR IPAddressWCharString[100];
    ::InetNtopW(AF_INET, &SocketAddress.sin_addr, IPAddressWCharString, len32(IPAddressWCharString));
        // sizeof(buffer)를 했을때, IPAddressWCharString의 원소가 2바이트 크기라 제대로 반환 안될수도 있음.
        // 그래서 따로 len32() 매크로 함수를 정의함.
    return wstring(IPAddressWCharString);
}

IN_ADDR USNetAddress::IP2Address(const WCHAR* InIPWCharString)
{
    IN_ADDR ResultAddress;
    ::InetPtonW(AF_INET, InIPWCharString, &ResultAddress);
    return ResultAddress;
}

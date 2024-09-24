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
        // sizeof(buffer)�� ������, IPAddressWCharString�� ���Ұ� 2����Ʈ ũ��� ����� ��ȯ �ȵɼ��� ����.
        // �׷��� ���� len32() ��ũ�� �Լ��� ������.
    return wstring(IPAddressWCharString);
}

IN_ADDR USNetAddress::IP2Address(const WCHAR* InIPWCharString)
{
    IN_ADDR ResultAddress;
    ::InetPtonW(AF_INET, InIPWCharString, &ResultAddress);
    return ResultAddress;
}

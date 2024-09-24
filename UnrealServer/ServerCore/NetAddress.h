#pragma once

class USNetAddress
{
public:
    USNetAddress() = default;

    USNetAddress(SOCKADDR_IN InSocketAddress);

    USNetAddress(wstring InIPString, uint16 InPortNumber);

    SOCKADDR_IN& GetSocketAddress() { return SocketAddress; }

    wstring	GetIPAddressWString();

    uint16 GetPort() { return ::ntohs(SocketAddress.sin_port); }

    static IN_ADDR	IP2Address(const WCHAR* InIPWCharString);

private:
    SOCKADDR_IN		SocketAddress = {};

};

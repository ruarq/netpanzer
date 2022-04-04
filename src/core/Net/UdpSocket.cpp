// Copyright (C) 2022 ruarq <https://github.com/ruarq>
//
// Permission is hereby granted, free of
// charge, to any person obtaining a copy of this software and associated documentation
// files (the “Software”), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright
// notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY
// KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "UdpSocket.hpp"

namespace NetPanzer::Net
{

UdpSocket::UdpSocket(const ProtocolFamily family)
	: Socket{ Protocol::Udp }
	, family{ family }
{
	switch (family)
	{
		case ProtocolFamily::Inet4:
			socketFd = socket((int)family, SOCK_DGRAM, (int)protocol);
			break;

		case ProtocolFamily::Inet6:
			socketFd = socket((int)family, SOCK_DGRAM, (int)protocol);
			break;

		case ProtocolFamily::Any:
			break;
	}
}

ssize_t UdpSocket::SendTo(const std::string &hostname, const Port port, const BufferView &buffer)
{
	const auto address = GetAddressInfo(hostname, port, family);
	if (!address)
	{
		return -1;
	}

	// This happens when the udp masterSocket was constructed with ProtocolFamily::Any,
	// since we can't construct a masterSocket when we don't know its family
	if (socketFd == NP_NET_INVALID_SOCKET_VALUE)
	{
		socketFd = socket(address->ai_family, SOCK_DGRAM, (int)protocol);
		family = (ProtocolFamily)address->ai_family;
	}

	return sendto(socketFd, buffer.Data(), buffer.Size(), 0, address->ai_addr, address->ai_addrlen);
}

Buffer
UdpSocket::ReceiveFrom(const std::string &hostname, const Port port, const size_t maxBufferSize)
{
	const auto address = GetAddressInfo(hostname, port, family);
	if (!address)
	{
		return Buffer{ 0 };
	}

	// If you're wondering about this, please look into the SentTo function
	if (socketFd == NP_NET_INVALID_SOCKET_VALUE)
	{
		socketFd = socket(address->ai_family, SOCK_DGRAM, (int)protocol);
		family = (ProtocolFamily)address->ai_family;
	}

	Buffer buffer{ maxBufferSize };
	const ssize_t bytesReceived =
		recvfrom(socketFd, buffer.Data(), buffer.Size(), 0, address->ai_addr, &address->ai_addrlen);

	buffer.Resize(bytesReceived);
	return buffer;
}

}

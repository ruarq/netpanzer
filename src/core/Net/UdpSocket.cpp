// Copyright (C) 2022  ruarq <https://github.com/ruarq>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
	}

	Buffer buffer{ maxBufferSize };
	const ssize_t bytesReceived =
		recvfrom(socketFd, buffer.Data(), buffer.Size(), 0, address->ai_addr, &address->ai_addrlen);

	buffer.Resize(bytesReceived);
	return buffer;
}

}

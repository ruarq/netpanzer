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

#include "Socket.hpp"

namespace NetPanzer::Net
{

constexpr int ProtocolToSocketType(const Protocol protocol)
{
	return protocol == Protocol::Tcp ? SOCK_STREAM : SOCK_DGRAM;
}

Socket::Socket(const Protocol protocol)
	: socketFd{ NP_NET_INVALID_SOCKET_VALUE }
	, protocol{ protocol }
{
}

Socket::~Socket()
{
	Close();
}

SocketFd Socket::NativeFd() const
{
	return socketFd;
}

UniqueAddrinfoPtr Socket::GetAddressInfo(const std::string &hostname,
	const Port port,
	const ProtocolFamily family) const
{
	addrinfo hints{};
	hints.ai_family = (int)family;
	hints.ai_protocol = (int)protocol;

	// NOTE: At his point we expect protocol to be either Tcp or Udp, and nothing else
	// that's why this should work (should)
	hints.ai_socktype = ProtocolToSocketType(protocol);

	// We have to convert port to a string since getaddrinfo only accepts strings :/
	const std::string portAsStr = std::to_string(port);

	addrinfo *address{};
	const int result = getaddrinfo(hostname.empty() ? nullptr : hostname.c_str(),
		portAsStr.c_str(),
		&hints,
		&address);
	if (result != 0)
	{
		// TODO(ruarq): If getaddrinfo, could address still contain some data?
		return MakeUniqueAddrinfoPtr(nullptr);
	}

	// By using a unique_ptr we don't have to remember to delete the result return by this function
	return MakeUniqueAddrinfoPtr(address);
}

void Socket::Close()
{
	close(socketFd);
	socketFd = NP_NET_INVALID_SOCKET_VALUE;
}

}

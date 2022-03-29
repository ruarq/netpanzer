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

#include "Socket.hpp"

namespace NetPanzer::Net
{

constexpr int ProtocolToSocketType(const Protocol protocol)
{
	return protocol == Protocol::Tcp ? SOCK_STREAM : SOCK_DGRAM;
}

Socket::Socket(const Protocol protocol)
	: socketFd{ NP_SOCKET_INVALID }
	, protocol{ protocol }
{
}

Socket::~Socket()
{
	Close();
}

SocketFd Socket::NativeHandle() const
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
	socketFd = NP_SOCKET_INVALID;
}

}

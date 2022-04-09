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

#ifndef NP_SOCKET_HPP
#define NP_SOCKET_HPP

#include <memory>

#include "../common.hpp"
#include "../platform.hpp"

#if defined(NP_OS_MACOSX) || defined(NP_OS_LINUX)
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sys/types.h>
	#include <unistd.h>
#elif defined(NP_OS_WINDOWS)
	#include <winsock.h>
#endif

namespace NetPanzer::Net
{

using Port = uint16_t;

#if defined(NP_OS_MACOSX) || defined(NP_OS_LINUX)
using SocketFd = int;
#elif defined(NP_OS_WINDOWS)
using SocketFd = SOCKET;
#endif

#define NP_NET_INVALID_SOCKET_VALUE ((SocketFd)-1)
#define NP_NET_PORT_TCP 42069
#define NP_NET_PORT_UDP 12345
#define NP_NET_DEFAULT_BUFFER_SIZE (1024 * 4)	 // 4 kB
#define NP_NET_DEFAULT_BACKLOG 5

// The hostname of this machine
#define NP_NET_LOCALHOST (std::string{})

enum class Protocol
{
	Tcp = IPPROTO_TCP,
	Udp = IPPROTO_UDP
};

enum class ProtocolFamily
{
	Inet4 = PF_INET,
	Inet6 = PF_INET6,
	Any = PF_UNSPEC
};

using UniqueAddrinfoPtr = std::unique_ptr<addrinfo, void (*)(addrinfo *)>;

/**
 * @brief Helper function to create std::unique_ptr<addrinfo>
 * @param info The addrinfo object
 * @return info as std::unique_ptr<addrinfo>
 */
NP_NODISCARD inline UniqueAddrinfoPtr MakeUniqueAddrinfoPtr(addrinfo *info)
{
	// The weird stuff is just a custom deleter, since addrinfo requires freeaddrinfo
	// and not free or delete
	return UniqueAddrinfoPtr{ info, [](addrinfo *info) {
								 freeaddrinfo(info);
							 } };
}

/**
 * @brief Socket wrapper. This is not meant to be used directly,
 * see Net::Udp::Socket and Net::Tcp::Socket
 */
class Socket
{
protected:
	/**
	 * @brief Initialize a masterSocket
	 * @param protocol The type of protocol the masterSocket uses
	 */
	explicit Socket(Protocol protocol);
	virtual ~Socket();

public:
	/**
	 * @brief Get the native handle of the masterSocket
	 * @return The native masterSocket handle
	 */
	NP_NODISCARD SocketFd NativeFd() const;

protected:
	/**
	 * @brief Get address information using the hostname, port and procotol family.
	 * @param hostname The hostname. Leave empty to get information about this host
	 * @param port The port
	 * @param family The protocol family
	 * @return Pointer to addrinfo* containing the address information.
	 * @return nullptr If something went wrong
	 */
	NP_NODISCARD UniqueAddrinfoPtr GetAddressInfo(const std::string &hostname,
		Port port,
		ProtocolFamily family) const;

	/**
	 * @brief Close the masterSocket
	 */
	void Close();

protected:
	SocketFd socketFd;
	Protocol protocol;
};

/**
 * @brief Compare two sockets for equality
 * @return true If they're the same socket
 * @return false If they're not the same socket
 */
template<typename TSocket>
bool operator==(const TSocket &a, const TSocket &b)
{
	return a.NativeFd() == b.NativeFd();
}

/**
 * @brief Compare two sockets for inequality
 * @return true If they're not the same socket
 * @return false If they're the same socket
 */
template<typename TSocket>
bool operator!=(const TSocket &a, const TSocket &b)
{
	return a.NativeFd() != b.NativeFd();
}

}

#endif

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

#ifndef NP_UDPSOCKET_HPP
#define NP_UDPSOCKET_HPP

#include "../Buffer.hpp"
#include "Socket.hpp"

namespace NetPanzer::Net
{

class UdpSocket : Socket
{
public:
	/**
	 * @brief Initialize a UDP socket. NOTE: If you're initializing with Net::ProtocolFamily::Any,
	 * the protocol family will be decided on first call to
	 * UdpSocket::SentTo or UdpSocket::ReceiveFrom automatically and can't and won't be
	 * changed afterwards.
	 * @param family
	 */
	explicit UdpSocket(ProtocolFamily family);

public:
	/**
	 * @brief Send some data to a host
	 * @param hostname The hostname
	 * @param port The port
	 * @param buffer The data
	 * @return The amount of bytes sent
	 */
	NP_NODISCARD ssize_t SendTo(const std::string &hostname, Port port, const BufferView &buffer);

	/**
	 * @brief Receive some data from a host
	 * @param hostname The hostname
	 * @param port The port
	 * @param maxBufferSize The max buffer size
	 * @return Buffer containing the data received
	 */
	NP_NODISCARD Buffer ReceiveFrom(const std::string &hostname,
		Port port,
		size_t maxBufferSize = NP_NET_DEFAULT_BUFFER_SIZE);

private:
	ProtocolFamily family;
};

}

#endif

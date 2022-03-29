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

#ifndef NP_TCPSOCKET_HPP
#define NP_TCPSOCKET_HPP

#include "../Buffer.hpp"
#include "Socket.hpp"

namespace NetPanzer::Net
{

class TcpSocket : Socket
{
public:
	/**
	 * @brief Initialize a TCP socket
	 */
	TcpSocket();

public:
	/**
	 * @brief Connect a connection to a host
	 * @param hostname The hostname
	 * @param port The port
	 * @return True if opening the connection was successful, otherwise false
	 */
	NP_NODISCARD bool
	Connect(const std::string &hostname, Port port, ProtocolFamily family = ProtocolFamily::Any);

	/**
	 * @brief Disconnect the socket
	 */
	void Disconnect();

	/**
	 * @brief Send data, not guaranteed that everything will be sent
	 * @param buffer The buffer to send
	 * @return The amount of bytes sent
	 */
	NP_NODISCARD ssize_t Send(const BufferView &buffer);

	/**
	 * @brief Send all data
	 * @param buffer The buffer
	 * @param packetSize The size per packet (0 means send as much as possible per iteration)
	 * @return The amount of bytes sent
	 */
	NP_NODISCARD ssize_t SendAll(const BufferView &buffer, size_t packetSize = 0);

	/**
	 * @brief Receive data, not guaranteed that everything will be received
	 * @param maxBufferSize The max buffer size
	 * @return Buffer containing the data received
	 */
	NP_NODISCARD Buffer Receive(size_t maxBufferSize = NP_NET_DEFAULT_BUFFER_SIZE);

	/**
	 * @brief Receive all data
	 * @param packetSize The size to read per packet
	 * @return Buffer containing the data received
	 */
	NP_NODISCARD Buffer ReceiveAll(size_t packetSize = 0);
};

}

#endif

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

#ifndef NP_TCPSOCKET_HPP
#define NP_TCPSOCKET_HPP

#include <thread>

#include "../Buffer.hpp"
#include "Socket.hpp"

namespace NetPanzer::Net
{

class TcpSocket : public Socket
{
public:
	/**
	 * @brief Initialize a TCP masterSocket
	 */
	TcpSocket();

	/**
	 * @brief Move constructor
	 * @param socket Socket to move
	 */
	TcpSocket(TcpSocket &&socket) noexcept;

	/**
	 * @brief Delete copy constructor
	 */
	TcpSocket(const TcpSocket &socket) = delete;

	/**
	 * @brief Initialize a TCP masterSocket with an existing masterSocket file descriptor
	 */
	explicit TcpSocket(SocketFd socket);

public:
	/**
	 * @brief Connect a connection to a host
	 * @param hostname The hostname
	 * @param port The port
	 * @return True if opening the connection was successful
	 * @return False if opening the connection failed
	 */
	NP_NODISCARD bool
	Connect(const std::string &hostname, Port port, ProtocolFamily family = ProtocolFamily::Any);

	/**
	 * @brief Disconnect the masterSocket
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
	ssize_t SendAll(const BufferView &buffer, size_t packetSize = 0);

	/**
	 * @brief Receive data, not guaranteed that everything will be received
	 * @param maxBufferSize The max buffer size
	 * @return Buffer containing the data received
	 */
	NP_NODISCARD Buffer Receive(size_t maxBufferSize = NP_NET_DEFAULT_BUFFER_SIZE);

	/**
	 * @brief Receive N bytes
	 * @param bytes The amount of bytes to receive
	 * @return Buffer containing the data received
	 */
	NP_NODISCARD Buffer ReceiveN(size_t bytes);

	/**
	 * @brief Bind this masterSocket to a name
	 * @param hostname The hostname
	 * @param port The port
	 * @param family The address family
	 * @return True on success
	 * @return False on failure
	 */
	NP_NODISCARD bool
	Bind(const std::string &hostname, Port port, ProtocolFamily family = ProtocolFamily::Any);

	/**
	 * @brief Use this masterSocket to listen for incoming connections
	 * @param backlog
	 * @return
	 */
	NP_NODISCARD bool Listen(int backlog = NP_NET_DEFAULT_BACKLOG);

	/**
	 * @brief Accept an incoming connection
	 * @return A masterSocket connected to the client
	 */
	NP_NODISCARD TcpSocket Accept();

	/**
	 * @brief Move assigment operator
	 */
	TcpSocket &operator=(TcpSocket &&socket) noexcept;

private:
	fd_set clients;
};

}

#endif

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

#ifndef NP_UDPSOCKET_HPP
#define NP_UDPSOCKET_HPP

#include "../Buffer.hpp"
#include "Socket.hpp"

namespace NetPanzer::Net
{

class UdpSocket : public Socket
{
public:
	/**
	 * @brief Initialize a UDP masterSocket.
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

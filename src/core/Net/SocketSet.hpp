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

#ifndef NP_SOCKETSET_HPP
#define NP_SOCKETSET_HPP

#include <cmath>

#include "../common.hpp"
#include "Socket.hpp"

namespace NetPanzer::Net
{

class SocketSet
{
public:
	/**
	 * @brief Add a socket to check for incoming data
	 * @param socket The socket
	 */
	void AddForRead(const Socket &socket);

	/**
	 * @brief Add a socket to check if it's readable
	 * @param socket The socket
	 */
	void AddForWrite(const Socket &socket);

	/**
	 * @brief Check if there is incoming data for that socket
	 * @param socket The socket
	 * @return true If there is incoming data
	 * @return false If there is no incoming data
	 */
	NP_NODISCARD bool IsDataAvailable(const Socket &socket) const;

	/**
	 * @brief Check if the socket is writeable
	 * @param socket The socket
	 * @return true If the socket is writeable
	 * @return false If the socket isn't writeable
	 */
	NP_NODISCARD bool IsWriteable(const Socket &socket) const;

	/**
	 * @brief Wait for input on the sockets of the set
	 * @param timeout The max time to wait for input in seconds. 0 is basically a poll,
	 * and anything less than 0 means to just wait until input is available
	 */
	void Select(float timeout = -1.0f);

private:
	fd_set masterWriteFds{};
	fd_set writeFds{};

	fd_set masterReadFds{};
	fd_set readFds{};

	SocketFd maxFd{};
};

}

#endif

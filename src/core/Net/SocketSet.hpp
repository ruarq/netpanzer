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

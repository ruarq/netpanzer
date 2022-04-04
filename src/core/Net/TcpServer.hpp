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

#ifndef NP_TCPSERVER_HPP
#define NP_TCPSERVER_HPP

#include <atomic>
#include <thread>

#include "../common.hpp"
#include "TcpSocket.hpp"

namespace NetPanzer::Net
{

class TcpServer
{
public:
	~TcpServer();

public:
	/**
	 * @brief Start running the server in it's own thread
	 */
	void AsyncRun();

	virtual void OnClientConnect(TcpSocket &&socket) = 0;
	virtual void OnReceive(TcpSocket &socket) = 0;

protected:
	void Accept(TcpSocket &&newClient);

private:
	void Select();
	TcpSocket &GetSocketByFd(SocketFd socketFd);

protected:
	TcpSocket master;
	std::vector<TcpSocket> clients;

private:
	std::thread thread;
	std::atomic_bool running = true;
};

}

#endif

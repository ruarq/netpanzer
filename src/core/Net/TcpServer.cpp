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

#include "TcpServer.hpp"

namespace NetPanzer::Net
{

TcpServer::~TcpServer()
{
	running = false;
	thread.join();
}

void TcpServer::AsyncRun()
{
	thread = std::thread([&]() {
		while (running)
		{
			Select();
		}
	});
}

void TcpServer::Accept(TcpSocket &&newClient)
{
	clients.push_back(std::move(newClient));
}

void TcpServer::Select()
{
	const SocketFd masterFd = master.NativeFd();
	int numFds = masterFd;

	fd_set readFds{};
	FD_SET(masterFd, &readFds);

	for (const TcpSocket &client : clients)
	{
		const SocketFd fd = client.NativeFd();
		FD_SET(fd, &readFds);

		if (fd > numFds)
		{
			numFds = fd;
		}
	}

	// TODO(ruarq): Some error handling needed here
	timeval timeout{ .tv_sec = 1, .tv_usec = 100'000 };
	select(numFds + 1, &readFds, nullptr, nullptr, &timeout);

	for (int fd = 0; fd < numFds + 1; ++fd)
	{
		const int readable = FD_ISSET(fd, &readFds);
		if (readable)
		{
			if (fd != masterFd)	   // Incoming data
			{
				OnReceive(GetSocketByFd(fd));
			}
			else	// New client
			{
				TcpSocket newClient = master.Accept();
				OnClientConnect(std::move(newClient));
			}
		}
	}
}

TcpSocket &TcpServer::GetSocketByFd(const SocketFd socketFd)
{
	for (TcpSocket &client : clients)
	{
		if (client.NativeFd() == socketFd)
		{
			return client;
		}
	}

	throw std::runtime_error("Net::TcpServer::GetSocketByFd() : No client with such socketFd");
}

}

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

#include <iostream>

#include <Net/SocketSet.hpp>
#include <Net/TcpSocket.hpp>
#include <common.hpp>

using namespace NetPanzer;
using namespace NetPanzer::Net;

int main()
{
	TcpSocket server;
	if (!server.Bind(NP_NET_LOCALHOST, NP_NET_PORT_TCP))
	{
		std::cout << "Bind failed\n";
		return 1;
	}

	if (!server.Listen())
	{
		std::cout << "Listen failed\n";
		return 1;
	}

	std::vector<TcpSocket> clients;

	SocketSet socketSet;
	socketSet.AddForRead(server);

	while (true)
	{
		socketSet.Select();
		if (socketSet.IsDataAvailable(server))
		{
			std::cout << "New connection\n";
			TcpSocket newSocket = server.Accept();
			socketSet.AddForRead(newSocket);
			clients.push_back(std::move(newSocket));
		}

		for (TcpSocket &client : clients)
		{
			if (socketSet.IsDataAvailable(client))
			{
				const Buffer received = client.Receive();
				for (TcpSocket &otherClient : clients)
				{
					if (otherClient != client)
					{
						otherClient.SendAll(BufferView{ received });
					}
				}
			}
		}
	}

	return 0;
}

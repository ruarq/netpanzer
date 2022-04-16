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

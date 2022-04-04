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

#include <Net/TcpServer.hpp>
#include <Net/TcpSocket.hpp>
#include <common.hpp>

using namespace NetPanzer;

class TcpChat : public Net::TcpServer
{
public:
	TcpChat()
	{
		master.Bind(NP_NET_THIS_HOSTNAME, NP_NET_PORT_TCP);
		master.Listen();
	}

public:
	void OnClientConnect(Net::TcpSocket &&newClient) override
	{
		const std::string_view verify = "netPanzer Client";
		const Buffer buffer = newClient.ReceiveN(verify.size());

		const std::string message{ buffer.begin(), buffer.end() };
		if (message == verify)
		{
			Accept(std::move(newClient));
		}
	}

	void OnReceive(Net::TcpSocket &client) override
	{
		const Buffer msg = client.Receive();
		for (Net::TcpSocket &socket : clients)
		{
			if (socket != client)
			{
				socket.SendAll(BufferView{ msg });
			}
		}
	}
};

int main()
{
	TcpChat chat;
	chat.AsyncRun();

	getchar();

	return 0;
}

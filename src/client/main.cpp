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

#include <Net/TcpSocket.hpp>
#include <common.hpp>

using namespace NetPanzer;

int main()
{
	Net::TcpSocket client;
	const bool connected = client.Connect(NP_NET_THIS_HOSTNAME, NP_NET_PORT_TCP);
	if (!connected)
	{
		std::cout << "Couldn't connect\n";
		return 1;
	}

	while (true)
	{
		std::cout << "Send: ";
		std::string input;
		std::getline(std::cin, input);

		if (input.empty())
		{
			break;
		}

		client.SendAll(BufferView{ input.data(), input.size() });
		Buffer received = client.ReceiveAll(input.size());
		std::cout << "Recv: " << std::string{ received.begin(), received.end() } << "\n";
	}

	return 0;
}

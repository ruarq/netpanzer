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
#include <Net/UdpSocket.hpp>
#include <common.hpp>

using namespace NetPanzer;

int main()
{
	const std::string_view httpRequest = "GET / HTTP/1.1\r\n"
										 "Host: www.example.com\r\n"
										 "Connection: close\r\n\r\n";

	Net::TcpSocket socket;
	const bool open = socket.Connect("www.example.com", 80);
	if (!open)
	{
		std::cout << "Couldn't open a connection!\n";
		return 1;
	}

	const ssize_t bytesSent = socket.SendAll(BufferView{ httpRequest.begin(), httpRequest.end() });
	if (bytesSent != httpRequest.size())
	{
		std::cout << "Couldn't send http request!\n";
		return 1;
	}

	const Buffer response{ socket.ReceiveAll() };
	std::string responseAsString{ response.begin(), response.end() };
	std::cout << responseAsString << "\n";

	return 0;
}

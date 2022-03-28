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

#include "TcpSocket.hpp"

namespace NetPanzer::Net
{

TcpSocket::TcpSocket()
	: Socket{ Protocol::Tcp }
{
}

bool TcpSocket::Connect(const std::string &hostname, Port port, ProtocolFamily family)
{
	if (socketFd != NP_SOCKET_INVALID)
	{
		Disconnect();
	}

	const auto address = GetAddressInfo(hostname, port, family);
	if (!address)
	{
		return false;
	}

	socketFd = socket(address->ai_family, SOCK_STREAM, (int)protocol);
	return connect(socketFd, address->ai_addr, address->ai_addrlen) == 0;
}

void TcpSocket::Disconnect()
{
	close(socketFd);
	socketFd = NP_SOCKET_INVALID;
}

ssize_t TcpSocket::Send(const BufferView &buffer)
{
	return send(socketFd, buffer.Data(), buffer.Size(), 0);
}

Buffer TcpSocket::Receive(const size_t maxBufferSize)
{
	Buffer buffer{ maxBufferSize };
	const ssize_t bytesReceived = recv(socketFd, buffer.Data(), buffer.Size(), 0);

	buffer.Resize(bytesReceived);
	return buffer;
}

}

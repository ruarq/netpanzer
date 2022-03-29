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
	Close();
}

ssize_t TcpSocket::Send(const BufferView &buffer)
{
	return send(socketFd, buffer.Data(), buffer.Size(), 0);
}

ssize_t TcpSocket::SendAll(const BufferView &buffer, size_t packetSize)
{
	if (packetSize == 0)
	{
		packetSize = buffer.Size();
	}

	ssize_t bytesSent = 0;
	do
	{
		ssize_t packetBytesSent = 0;
		do
		{
			packetBytesSent +=
				Send(BufferView{ buffer.Data() + bytesSent, buffer.Size() - bytesSent });
		}
		while (packetBytesSent < packetSize && bytesSent < buffer.Size());
		bytesSent += packetBytesSent;
	}
	while (bytesSent < buffer.Size());

	return bytesSent;
}

Buffer TcpSocket::Receive(const size_t maxBufferSize)
{
	Buffer buffer{ maxBufferSize };
	const ssize_t bytesReceived = recv(socketFd, buffer.Data(), buffer.Size(), 0);

	buffer.Resize(bytesReceived);
	return buffer;
}

Buffer TcpSocket::ReceiveAll(size_t packetSize)
{
	if (packetSize == 0)
	{
		packetSize = NP_NET_DEFAULT_BUFFER_SIZE;
	}

	Buffer buffer{ 0 };
	Buffer received{ Receive(packetSize) };

	while (!received.Empty())
	{
		// Cache buffer.Size() because buffer.Resize() changes it
		const size_t bufferSize = buffer.Size();

		// Resize the buffer to fit the received data
		buffer.Resize(bufferSize + received.Size());

		// Copy the received data into the buffer
		std::memcpy(buffer.Data() + bufferSize, received.Data(), received.Size());

		received = Receive(packetSize);
	}

	return buffer;
}

}

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

#include "TcpSocket.hpp"

namespace NetPanzer::Net
{

TcpSocket::TcpSocket()
	: Socket{ Protocol::Tcp }
{
}

TcpSocket::TcpSocket(TcpSocket &&socket) noexcept
	: TcpSocket()
{
	this->operator=(std::move(socket));
}

TcpSocket::TcpSocket(const SocketFd socket)
	: TcpSocket{}
{
	socketFd = socket;
}

bool TcpSocket::Connect(const std::string &hostname, Port port, ProtocolFamily family)
{
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

	if (bytesReceived > 0)
	{
		buffer.Resize(bytesReceived);
	}
	else
	{
		buffer.Clear();
	}

	return buffer;
}

Buffer TcpSocket::ReceiveN(size_t bytes)
{
	if (bytes == 0)
	{
		bytes = NP_NET_DEFAULT_BUFFER_SIZE;
	}

	Buffer buffer{ bytes };

	size_t bytesReceived = 0;
	while (bytesReceived < bytes)
	{
		Buffer received = Receive(bytes - bytesReceived);
		std::memcpy(buffer.Data() + bytesReceived, received.Data(), received.Size());
		bytesReceived += received.Size();
	}

	return buffer;
}

bool TcpSocket::Bind(const std::string &hostname, const Port port, const ProtocolFamily family)
{
	// TODO(ruarq): setsockopts
	const auto address = GetAddressInfo(hostname, port, family);
	socketFd = socket(address->ai_family, SOCK_STREAM, (int)protocol);
	return bind(socketFd, address->ai_addr, address->ai_addrlen) == 0;
}

bool TcpSocket::Listen(const int backlog)
{
	return listen(socketFd, backlog) == 0;
}

TcpSocket TcpSocket::Accept()
{
	return TcpSocket{ accept(socketFd, nullptr, nullptr) };
}

TcpSocket &TcpSocket::operator=(TcpSocket &&socket) noexcept
{
	socketFd = socket.socketFd;
	socket.socketFd = NP_NET_INVALID_SOCKET_VALUE;
	return *this;
}

}

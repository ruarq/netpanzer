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

#include "SocketSet.hpp"

namespace NetPanzer::Net
{

void SocketSet::AddForRead(const Socket &socket)
{
	FD_SET(socket.NativeFd(), &masterReadFds);
	maxFd = std::max(socket.NativeFd(), maxFd);
}

void SocketSet::AddForWrite(const Socket &socket)
{
	FD_SET(socket.NativeFd(), &masterWriteFds);
	maxFd = std::max(socket.NativeFd(), maxFd);
}

bool SocketSet::IsDataAvailable(const Socket &socket) const
{
	return FD_ISSET(socket.NativeFd(), &readFds);
}

bool SocketSet::IsWriteable(const Socket &socket) const
{
	return FD_ISSET(socket.NativeFd(), &writeFds);
}

void SocketSet::Select(const float fTimeout)
{
	// We don't want to overwrite masterReadFds or masterWriteFds
	FD_COPY(&masterReadFds, &readFds);
	FD_COPY(&masterWriteFds, &writeFds);

	// tv_sec is fTimeout in seconds without fraction
	// tv_usec is fTimeout with only the fraction.
	// The total timeout will be tv_sec + tv_usec
	timeval timeout{ .tv_sec = (int)fTimeout,
		.tv_usec = (int)((fTimeout - std::floor(fTimeout)) * 1000000.0f) };

	// Don't pass a timeout value if we want to just wait for input
	// which is when fTimeout is less than 0
	timeval *pTimeout{};
	if (fTimeout >= 0.0f)
	{
		pTimeout = &timeout;
	}

	const int result = select(maxFd + 1, &readFds, &writeFds, nullptr, pTimeout);
	if (result == -1)
	{
		// TODO(ruarq): Error handling stuff things bla bla
	}
}

}

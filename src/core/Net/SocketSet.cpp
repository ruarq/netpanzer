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

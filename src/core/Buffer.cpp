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

#include "Buffer.hpp"

namespace NetPanzer
{

Buffer::Buffer(const size_t size)
	: data{ new Byte[size] }
	, size{ size }
{
}

Buffer::Buffer(const Byte *data, const size_t size)
{
	this->data = new Byte[size];
	std::memcpy(this->data, data, size);
	this->size = size;
}

Buffer::~Buffer()
{
	delete[] data;
}

Buffer::Buffer(Buffer &&buffer) noexcept
{
	operator=(std::move(buffer));
}

void Buffer::Resize(const size_t newSize)
{
	if (newSize > size)
	{
		// allocate a bigger buffer
		auto buffer = new Byte[newSize];

		// copy the data and delete the old buffer
		std::memcpy(buffer, data, size);
		delete[] data;

		// set new buffer
		data = buffer;
	}

	size = newSize;
}

Byte *Buffer::Data()
{
	return data;
}

size_t Buffer::Size() const
{
	return size;
}

bool Buffer::Empty() const
{
	return Size() == 0;
}

BufferView::BufferView(const Byte *data, const size_t size)
	: data{ data }
	, size{ size }
{
}

const Byte *BufferView::Data() const
{
	return data;
}

size_t BufferView::Size() const
{
	return size;
}

}

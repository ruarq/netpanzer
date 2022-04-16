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
	this->operator=(std::move(buffer));
}

Byte *Buffer::begin()
{
	return data;
}

const Byte *Buffer::begin() const
{
	return data;
}

Byte *Buffer::end()
{
	return data + size;
}

const Byte *Buffer::end() const
{
	return data + size;
}

void Buffer::Resize(const size_t newSize)
{
	if (newSize != size)
	{
		// allocate a bigger buffer
		auto buffer = new Byte[newSize];

		// copy the data and delete the old buffer
		std::memcpy(buffer, data, std::min(size, newSize));
		delete[] data;

		// set new buffer & size
		data = buffer;
		size = newSize;
	}
}

void Buffer::Clear()
{
	Resize(0);
}

Byte *Buffer::Data()
{
	return data;
}

const Byte *Buffer::Data() const
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

Byte &Buffer::operator[](const size_t index)
{
	return data[index];
}

Buffer &Buffer::operator=(Buffer &&buffer) noexcept
{
	data = buffer.data;
	size = buffer.size;

	buffer.data = nullptr;
	buffer.size = 0;

	return *this;
}

BufferView::BufferView(const Buffer &buffer)
	: BufferView{ buffer.Data(), buffer.Size() }
{
}

BufferView::BufferView(const Byte *data, const size_t size)
	: data{ data }
	, size{ size }
{
}

BufferView::BufferView(const Byte *first, const Byte *last)
	: BufferView{ first, (size_t)(last - first) }
{
}

const Byte *BufferView::begin() const
{
	return data;
}

const Byte *BufferView::end() const
{
	return data + size;
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

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

#ifndef NP_BUFFER_HPP
#define NP_BUFFER_HPP

#include "common.hpp"

namespace NetPanzer
{

class Buffer
{
public:
	/**
	 * @brief Construct a empty buffer
	 * @param size The size of the empty buffer
	 */
	explicit Buffer(size_t size);

	/**
	 * @brief Construct a buffer by copying the data
	 * @param data The data (will be copied!)
	 * @param size The size of the data in bytes
	 */
	Buffer(const Byte *data, size_t size);
	~Buffer();

	/**
	 * @brief Sorry! We don't copy buffers, we hate it ;)
	 */
	Buffer(const Buffer &buffer) = delete;

	/**
	 * @brief Move the buffer
	 */
	Buffer(Buffer &&buffer) noexcept;

public:
	/**
	 * @brief Pointer to the beginning of the buffer
	 */
	NP_NODISCARD Byte *begin();

	/**
	 * @brief Pointer to the beginning of the buffer
	 */
	NP_NODISCARD const Byte *begin() const;

	/**
	 * @brief Pointer to the end of the buffer
	 */
	NP_NODISCARD Byte *end();

	/**
	  * @brief Pointer to the end of the buffer
	  */
	NP_NODISCARD const Byte *end() const;

	/**
	 * @brief Resize the buffer
	 * @param newSize The new size of the buffer
	 */
	void Resize(size_t newSize);

	/**
	 * @brief Clear the buffer
	 */
	void Clear();

	/**
	 * @brief Get the stored data
	 * @return Byte* to the data
	 */
	NP_NODISCARD Byte *Data();

	/**
	 * @brief Get the stored data
	 * @return const Byte* to the data
	 */
	NP_NODISCARD const Byte *Data() const;

	/**
	 * @brief Get the size of the stored data
	 * @return The size of the data in bytes
	 */
	NP_NODISCARD size_t Size() const;

	/**
	 * @brief Check if the buffer is empty
	 * @return True if the buffer is empty, false otherwise
	 */
	NP_NODISCARD bool Empty() const;

	/**
	 * @brief Get the byte at n-th position in the buffer
	 * @param index The n-th position
	 * @return The byte at the n-th position
	 */
	NP_NODISCARD Byte &operator[](size_t index);

	/**
	 * @brief Move the buffer
	 */
	Buffer &operator=(Buffer &&buffer) noexcept;

private:
	Byte *data{};
	size_t size{};
};

class BufferView
{
public:
	/**
	 * @brief Construct a buffer view using a Buffer object
	 * @param buffer The buffer object
	 */
	explicit BufferView(const Buffer &buffer);

	/**
	 * @brief Construct a buffer view. The data the view points to has to be alive
	 * as long as the buffer view is alive
	 * @param data Pointer to the data (will NOT be copied!)
	 * @param size The size of the data in bytes
	 */
	BufferView(const Byte *data, size_t size);

	/**
	 * @brief Construct a buffer view. The data the view points to has to be alive
	 * as long as the buffer view is alive
	 * @param first Pointer to the first byte of the buffer
	 * @param last Pointer to the last byte of the buffer
	 */
	BufferView(const Byte *first, const Byte *last);

public:
	/**
	 * @brief Pointer to the beginning of the buffer
	 */
	NP_NODISCARD const Byte *begin() const;

	/**
	  * @brief Pointer to the end of the buffer
	  */
	NP_NODISCARD const Byte *end() const;

	/**
	 * @brief Get the data the view points to
	 * @return const Byte* to the data
	 */
	NP_NODISCARD const Byte *Data() const;

	/**
	 * @brief Get the size of the data the view points to
	 * @return The size of the buffer the data points to
	 */
	NP_NODISCARD size_t Size() const;

private:
	const Byte *const data;	   ///< Pointer to the data
	const size_t size;		   ///< Size of the data
};

}

#endif	  //NP_BUFFER_HPP

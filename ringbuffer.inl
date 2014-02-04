// ringbuffer.inl

/* © 2013 Leonhardt Schwarz, David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * Foobar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ringbuffer.hpp"

template <typename T>
RingBuffer<T>::RingBuffer(uchar size) :
	m_bufferSize(size),
	m_count(0)
{
}

template <typename T>
RingBuffer<T>::~RingBuffer()
{
}

template <typename T>
void RingBuffer<T>::clear()
{
	m_count = 0;
	m_buffer.clear();
}

template <typename T>
void RingBuffer<T>::push(const T& inputItem)
{
	m_buffer.push_back(inputItem);

	// Lösche das erste Element wenn der Buffer voll ist
	if (++m_count > m_bufferSize) {
		m_count = m_bufferSize;
		m_buffer.pop_front();
	}
}

template <typename T>
T RingBuffer<T>::pop()
{
	T result = T();

	// überprüfe ob es ein Element gibt
	if (!m_buffer.isEmpty()) {
		// Liest das jetzige Element aus
		result = m_buffer.last();

		if (--m_count < 0) {
			m_count = 0;
		} else {
			m_buffer.pop_back();
		}
	}

	return result;
}

template <typename T>
T RingBuffer<T>::first() const
{
	if (!m_buffer.isEmpty()) {
		return m_buffer.first();
	} else {
		return T();
	}
}

template <typename T>
T RingBuffer<T>::last() const
{
	if (!m_buffer.isEmpty()) {
		return m_buffer.last();
	} else {
		return T();
	}
}

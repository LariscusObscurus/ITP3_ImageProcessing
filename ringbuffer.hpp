/* © 2013 Leonhardt Schwarz, David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * ImageProcessing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageProcessing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageProcessing.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QList>

template <typename T>
class RingBuffer
{
public:
	explicit RingBuffer(uchar size);
	~RingBuffer();
	void clear();
	void push(const T& inputItem);
	T pop();
	T first() const;
	T last() const;

private:
	RingBuffer(const RingBuffer& thereShallBeOnlyOne){}

	uchar m_bufferSize;
	uchar m_count;
	QList<T> m_buffer;
};

#include "ringbuffer.inl"

#endif // RINGBUFFER_H

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

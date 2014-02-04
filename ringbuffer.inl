// ringbuffer.inl

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

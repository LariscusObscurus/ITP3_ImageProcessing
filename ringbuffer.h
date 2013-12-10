#ifndef RINGBUFFER_H
#define RINGBUFFER_H

template<typename T> class RingBuffer
{
public:
	explicit RingBuffer(unsigned int size) :
		m_bufferSize(size - 1),
		m_index(0)
	{
		m_buffer = new T[size]();
	}

	~RingBuffer()
	{
		delete[] m_buffer;
	}

	void push(T inputItem)
	{
		m_buffer[m_index++] = inputItem;
		if(m_index > m_bufferSize) {
			m_index = 0;
		}
	}

	T pop()
	{
		if(--m_index > m_bufferSize) {
			m_index = m_bufferSize;
		}
		T result = m_buffer[m_index];
		m_buffer[m_index] = T();
		return result;
	}

private:
	RingBuffer(const RingBuffer& thereShallBeOnlyOne){}

	unsigned int m_bufferSize;
	unsigned int m_index;
	T * m_buffer;
};

#endif // RINGBUFFER_H

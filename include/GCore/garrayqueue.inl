#ifndef _CORE_ARRAY_QUEUE_INLINE_
#define _CORE_ARRAY_QUEUE_INLINE_

#define G_QUEUE_DEFAULT_CAPACITY 1024

namespace gsystem { // gsystem

template <typename DataT>
DataT GArrayQueue<DataT>::front()
{
	if (m_nFront != m_nRear)
		return m_tArray[m_nFront];
};

template <typename DataT>
bool GArrayQueue<DataT>::pop()
{
	if (m_nFront == m_nRear)
		return false;
	m_nFront = (m_nFront + 1) % maxsize;
	return true;
};

template <typename DataT>
bool GArrayQueue<DataT>::push(T t)
{
	if ((m_nRear + 1) % maxsize == m_nFront)
		return false;
	m_tArray[m_nRear] = t;
	m_nRear = (m_nRear + 1) % maxsize;
	return true;
};

template <typename DataT>
gbool GArrayQueue<DataT>::IsEmpty() const
{
	if (m_nFront == m_nRear)
		return true;
	else
		return false;
};

template <typename DataT>
int GArrayQueue<DataT>::Size()
{
	return (m_nRear - m_nFront + maxsize) % maxsize;
};

} // namespace gsystem

#undef G_QUEUE_DEFAULT_CAPACITY

#endif // _CORE_ARRAY_QUEUE_INLINE_
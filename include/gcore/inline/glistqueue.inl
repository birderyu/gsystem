#ifndef _CORE_LIST_QUEUE_INLINE_
#define _CORE_LIST_QUEUE_INLINE_

namespace gsystem {

template <typename T> GINLINE
GListQueue<T>::GListQueue()
	: m_tList()
{

}

template<typename T> GINLINE 
GListQueue<T>::GListQueue(const GListQueue<T> &queue)
	: m_tList(queue.m_tList)
{

}

template<typename T> GINLINE 
GListQueue<T>::GListQueue(GListQueue<T> &&queue)
	: m_tList(GMove(queue.m_tList))
{

}

template<typename T> GINLINE
GListQueue<T>& GListQueue<T>::operator=(const GListQueue<T> &queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tList = queue.m_tList;
	return *this;
}

template<typename T> GINLINE
GListQueue<T>& GListQueue<T>::operator=(GListQueue<T> &&queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tList = GMove(queue.m_tList);
	return *this;
}

template <typename T> GINLINE
gsize GListQueue<T>::Size() const
{
	return m_tList.Size();
}

template <typename T> GINLINE
gbool GListQueue<T>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template <typename T> GINLINE
gvoid GListQueue<T>::Destroy()
{
	m_tList.RemoveAll();
}

template <typename T> GINLINE
gvoid GListQueue<T>::Clear()
{
	m_tList.RemoveAll();
}

template <typename T> GINLINE
gvoid GListQueue<T>::EnQueue(const T &value)
{
	m_tList.AddLast(value);
}

template <typename T> GINLINE
gvoid GListQueue<T>::EnQueue(T &&value)
{
	m_tList.AddLast(GForward<T>(value));
}

template <typename T> GINLINE
gbool GListQueue<T>::DeQueue(T *value)
{
	if (IsEmpty())
	{
		return false;
	}
	m_tList.RemoveFirst(value);
	return true;
}

template <typename T> GINLINE
const T &GListQueue<T>::Head() const
{
	return m_tList.GetFirstValue();
}

template <typename T> GINLINE
T &GListQueue<T>::Head()
{
	return m_tList.GetFirstValue();
}

}

#endif // _CORE_LIST_QUEUE_INLINE_
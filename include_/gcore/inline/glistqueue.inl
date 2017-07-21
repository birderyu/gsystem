#ifndef _CORE_LIST_QUEUE_INLINE_
#define _CORE_LIST_QUEUE_INLINE_

namespace gsystem {

template <typename DataT> GINLINE
GListQueue<DataT>::GListQueue()
	: m_tList()
{

}

template<typename DataT> GINLINE 
GListQueue<DataT>::GListQueue(const GListQueue<DataT> &queue)
	: m_tList(queue.m_tList)
{

}

template<typename DataT> GINLINE 
GListQueue<DataT>::GListQueue(GListQueue<DataT> &&queue)
	: m_tList(GMove(queue.m_tList))
{

}

template<typename DataT> GINLINE
GListQueue<DataT>& GListQueue<DataT>::operator=(const GListQueue<DataT> &queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tList = queue.m_tList;
	return *this;
}

template<typename DataT> GINLINE
GListQueue<DataT>& GListQueue<DataT>::operator=(GListQueue<DataT> &&queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tList = GMove(queue.m_tList);
	return *this;
}

template <typename DataT> GINLINE
gsize GListQueue<DataT>::Size() const
{
	return m_tList.Size();
}

template <typename DataT> GINLINE
gbool GListQueue<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template <typename DataT> GINLINE
gvoid GListQueue<DataT>::Destroy()
{
	m_tList.RemoveAll();
}

template <typename DataT> GINLINE
gvoid GListQueue<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template <typename DataT> GINLINE
gvoid GListQueue<DataT>::EnQueue(const DataT &data)
{
	m_tList.AddLast(data);
}

template <typename DataT> GINLINE
gvoid GListQueue<DataT>::EnQueue(DataT &&data)
{
	m_tList.AddLast(GForward<DataT>(data));
}

template <typename DataT> GINLINE
gvoid GListQueue<DataT>::DeQueue(DataT *data)
{
	m_tList.RemoveFirst(data);
}

template <typename DataT> GINLINE
const DataT &GListQueue<DataT>::Head() const
{
	return m_tList.GetFirstValue();
}

template <typename DataT> GINLINE
DataT &GListQueue<DataT>::Head()
{
	return m_tList.GetFirstValue();
}

}

#endif // _CORE_LIST_QUEUE_INLINE_
#ifndef _CORE_LIST_STACK_INLINE_
#define _CORE_LIST_STACK_INLINE_

namespace gsystem { // gsystem

template<typename DataT>
GINLINE GListStack<DataT>::GListStack() 
	: m_tList()
{

}

template<typename DataT>
GINLINE GListStack<DataT>::GListStack(const GListStack<DataT> &stack)
	: m_tList(stack.m_tList)
{

}

template<typename DataT>
GINLINE GListStack<DataT>::GListStack(GListStack<DataT> &&stack)
	:m_tList(GMove(stack.m_tList))
{

}

template<typename DataT> GINLINE
GListStack<DataT>& GListStack<DataT>::operator=(const GListStack<DataT> &stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tList = stack.m_tList;
	return *this;
}

template<typename DataT> GINLINE
GListStack<DataT>& GListStack<DataT>::operator=(GListStack<DataT> &&stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tList = GMove(stack.m_tList);
	return *this;
}

template<typename DataT>
GINLINE gbool GListStack<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template<typename DataT> GINLINE 
gvoid GListStack<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template<typename DataT> GINLINE
gvoid GListStack<DataT>::Destroy()
{
	m_tList.RemoveAll();
}

template<typename DataT>
GINLINE gsize GListStack<DataT>::Size() const
{
	return m_tList.Size();
}

template<typename DataT>
GINLINE gvoid GListStack<DataT>::Push(const DataT& data)
{
	m_tList.AddFirst(data);
}

template<typename DataT>
GINLINE gvoid GListStack<DataT>::Push(DataT &&data)
{
	m_tList.AddFirst(GForward<DataT>(data));
}

template<typename DataT>
GINLINE gvoid GListStack<DataT>::Pop(DataT *data)
{
	if (IsEmpty())
	{
		return;
	}

	if (data)
	{
		*data = GMove(m_tList.GetFirstData());
	}

	m_tList.RemoveFirst();
}

template<typename DataT>
GINLINE const DataT &GListStack<DataT>::Top() const
{
	return m_tList.GetFirstData();
}

template<typename DataT>
GINLINE DataT &GListStack<DataT>::Top()
{
	return m_tList.GetFirstData();
}

} // namespace gsystem

#endif // _CORE_LIST_STACK_INLINE_
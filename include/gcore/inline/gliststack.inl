#ifndef _CORE_LIST_STACK_INLINE_
#define _CORE_LIST_STACK_INLINE_

namespace gsystem { // gsystem

template<typename T>
GINLINE GListStack<T>::GListStack() 
	: m_tList()
{

}

template<typename T>
GINLINE GListStack<T>::GListStack(const GListStack<T> &stack)
	: m_tList(stack.m_tList)
{

}

template<typename T>
GINLINE GListStack<T>::GListStack(GListStack<T> &&stack)
	:m_tList(GMove(stack.m_tList))
{

}

template<typename T> GINLINE
GListStack<T>& GListStack<T>::operator=(const GListStack<T> &stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tList = stack.m_tList;
	return *this;
}

template<typename T> GINLINE
GListStack<T>& GListStack<T>::operator=(GListStack<T> &&stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tList = GMove(stack.m_tList);
	return *this;
}

template<typename T>
GINLINE gbool GListStack<T>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template<typename T> GINLINE 
gvoid GListStack<T>::Clear()
{
	m_tList.RemoveAll();
}

template<typename T> GINLINE
gvoid GListStack<T>::Destroy()
{
	m_tList.RemoveAll();
}

template<typename T>
GINLINE gsize GListStack<T>::Size() const
{
	return m_tList.Size();
}

template<typename T>
GINLINE gvoid GListStack<T>::Push(const T& value)
{
	m_tList.AddFirst(value);
}

template<typename T>
GINLINE gvoid GListStack<T>::Push(T &&value)
{
	m_tList.AddFirst(GForward<T>(value));
}

template<typename T>
GINLINE gbool GListStack<T>::Pop(T *value)
{
	if (IsEmpty())
	{
		return false;
	}
	m_tList.RemoveFirst(value);
	return true;
}

template<typename T>
GINLINE const T &GListStack<T>::Top() const
{
	return m_tList.GetFirstValue();
}

template<typename T>
GINLINE T &GListStack<T>::Top()
{
	return m_tList.GetFirstValue();
}

} // namespace gsystem

#endif // _CORE_LIST_STACK_INLINE_
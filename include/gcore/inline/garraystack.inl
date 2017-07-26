#ifndef _CORE_ARRAY_STACK_INLINE_
#define _CORE_ARRAY_STACK_INLINE_

#include "gutility.h"

namespace gsystem { // gsystem

template<typename T>
GINLINE GArrayStack<T>::GArrayStack(gsize capacity)
	: m_TopCursor(GDynamicArray<T>::NULL_POS), m_tArray(capacity)
{
	
}

template<typename T>
GINLINE GArrayStack<T>::GArrayStack(const GArrayStack<T> &stack)
	: m_TopCursor(stack.m_TopCursor)
	, m_tArray(stack.m_tArray)
{
	
}

template<typename T>
GINLINE GArrayStack<T>::GArrayStack(GArrayStack<T> &&stack)
	: m_TopCursor(stack.m_TopCursor)
	, m_tArray(GMove(stack.m_tArray))
{
	stack.m_TopCursor = GDynamicArray<T>::NULL_POS;
}

template<typename T>
GINLINE GArrayStack<T>& GArrayStack<T>::operator=(const GArrayStack<T> &stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tArray = stack.m_tArray;
	m_TopCursor = stack.m_TopCursor;
	return *this;
}

template<typename T>
GINLINE GArrayStack<T>& GArrayStack<T>::operator=(GArrayStack<T> &&stack)
{
	if (this == &stack)
	{
		return *this;
	}
	// 不需要再调用销毁方法，因为GDynamicArray的移动操作符已经处理了原数据的销毁
	m_tArray = GMove(stack.m_tArray);
	m_TopCursor = stack.m_TopCursor;
	stack.m_TopCursor = GDynamicArray<T>::NULL_POS;
	return *this;
}

template<typename T>
GINLINE gsize GArrayStack<T>::Size() const
{
	if (m_TopCursor == GDynamicArray<T>::NULL_POS)
	{
		return 0;
	}
	return m_TopCursor + 1;
}

template<typename T>
GINLINE gbool GArrayStack<T>::IsEmpty() const
{
	return GDynamicArray<T>::NULL_POS == m_TopCursor;
}

template<typename T>
GINLINE gvoid GArrayStack<T>::Clear()
{
	m_tArray.Clear();
	m_TopCursor = GDynamicArray<T>::NULL_POS;
}

template<typename T>
GINLINE gvoid GArrayStack<T>::Destroy()
{
	m_tArray.Destroy();
	m_TopCursor = GDynamicArray<T>::NULL_POS;
}

template<typename T>
GINLINE gvoid GArrayStack<T>::Push(const T &value)
{
	if (Fill())
	{
		// 数组已经充满了，需要扩容
		Reserve(Capacity() + 1);
	}
	if (m_TopCursor == GDynamicArray<T>::NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = value;
	}
	else
	{
		m_tArray[++m_TopCursor] = value;
	}
}


template<typename T>
GINLINE gvoid GArrayStack<T>::Push(T &&value)
{
	if (Fill())
	{
		// 数组已经充满了，需要扩容
		Reserve(Capacity() + 1);
	}
	if (m_TopCursor == GDynamicArray<T>::NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = GForward<T>(value);
	}
	else
	{
		m_tArray[++m_TopCursor] = GForward<T>(value);
	}
}

template<typename T>
GINLINE gbool GArrayStack<T>::Pop(T* value = GNULL)
{
	if (IsEmpty())
	{
		return false;
	}
	if (value)
	{
		// 将元素移走，而非拷贝
		*value = GMove(m_tArray[m_TopCursor]);
	}
	// 销毁元素
	GDestruct(&m_tArray[m_TopCursor]);

	// 游标前移
	if (m_TopCursor == 0)
	{
		m_TopCursor = GDynamicArray<T>::NULL_POS;
	}
	else
	{
		--m_TopCursor;
	}
	return true;
}

template<typename T>
GINLINE const T &GArrayStack<T>::Top() const
{
	GASSERT(m_TopCursor != GDynamicArray<T>::NULL_POS);
	return m_tArray[m_TopCursor];
}

template<typename T>
GINLINE T &GArrayStack<T>::Top()
{
	GASSERT(m_TopCursor != GDynamicArray<T>::NULL_POS);
	return m_tArray[m_TopCursor];
}

template<typename T> GINLINE
gsize GArrayStack<T>::Capacity() const
{
	return m_tArray.Size();
}

template<typename T> GINLINE 
gvoid GArrayStack<T>::Reserve(gsize capacity)
{
	if (IsEmpty()) 
	{
		// 栈已经为空了，可以销毁栈
		Destroy();
	}

	gsize old_capacity = Capacity();
	old_capacity += (old_capacity / 2);
	m_tArray.Resize(old_capacity > capacity ? old_capacity : capacity);
}

template<typename T>
GINLINE gbool GArrayStack<T>::Fill() const
{
	gsize capacity = Capacity();
	if (m_TopCursor == GDynamicArray<T>::NULL_POS && 0 == capacity)
	{
		return true;
	}
	else if (m_TopCursor == GDynamicArray<T>::NULL_POS)
	{
		return false;
	}
	return m_TopCursor >= capacity - 1;
}

} // namespace gsystem

#endif // _CORE_ARRAY_STACK_INLINE_
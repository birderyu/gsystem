/// 使用数组实现

#ifndef _CSCORE_VECTOR_H_
#define _CSCORE_VECTOR_H_

#include "CsArray.h"

#define CS_DEFAULT_VECTOR_SIZE			5
#define CS_DEFAULT_VECTOR_CAPACITY		0.5

template <typename T>
class CsVector :public CsObject
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

public:
	CsVector();
	explicit CsVector(const cs_size_t len, const &T t = T());
	cs_bool Reserve(const cs_size_t len) const;
	cs_bool Resize(const cs_size_t len) const;

	cs_size_t Size() const;
	cs_size_t Capacity() const;
	cs_bool IsEmpty() const;
	void Clear();

	T &operator[](const size_t i);
	T operator[](const size_t i) const;

	void PushBack(const T &t);
	void PushFront(const T &t);
	void PopBack();
	void PopFront();

private:
	cs_size_t MemSize() const;
	size_t RealID(const size_t i) const;
	cs_bool Valid() const;

	CsArray<T> m_tArray;

	// 头指针，指向首元素，初始值为-1
	cs_int m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为-1
	cs_int m_nTail;
};

template <typename T>
CsVector<T>::CsVector()
:CsArray(), m_nHead(-1), m_nTail(-1)
{
	
}

template <typename T>
CsVector<T>::CsVector(const cs_size_t len, const &T t)
:m_tArray(len, t), m_nHead(0), m_nTail(len)
{
	if (len <= 0)
	{
		m_nHead = m_nTail = -1;
	}
}

template <typename T>
cs_bool CsVector<T>::Reserve(const cs_size_t len) const
{
	if (len <= Capacity())
	{
		// 无需扩容
		return true;
	}
	CsArray tArray(len);

}

template <typename T>
cs_bool CsVector<T>::Resize(const cs_size_t len) const
{

}

template <typename T>
cs_size_t CsVector<T>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename T>
cs_size_t CsVector<T>::Capacity() const
{
	if (!Valid())
	{
		return 0;
	}
	return MemSize() - m_nHead;
}

template <typename T>
cs_bool CsVector<T>::IsEmpty() const
{
	return Size() == 0;
}

template <typename T>
void CsVector<T>::Clear()
{
	m_tArray.Clear();
	m_nHead = m_nTail = -1;
}

template <typename T>
T &CsVector<T>::operator[](const size_t i)
{
	return m_tArray[RealID(i)];
}

template <typename T>
T CsVector<T>::operator[](const size_t i) const
{
	return m_tArray[RealID(i)];
}

template <typename T>
void CsVector<T>::PushBack(const T &t)
{
	if (!Valid())
	{
		if (!m_tArray.Resize(1, t))
		{
			return;
		}
		m_nHead = 0;
		m_nTail = 1;
		return;
	}
	cs_size_t nCapacity = Capacity();
	if (m_nTail == Capacity())
	{
		cs_size_t nMemSize = MemSize();
		if (!m_tArray.Resize(nMemSize + 1, t))
		{
			return;
		}
		++m_nTail;
	}
	else
	{
		m_tArray[++m_nTail - 1] = t;
	}
}

template <typename T>
void CsVector<T>::PushFront(const T &t)
{
	if (!Valid())
	{
		if (!m_tArray.Resize(1, t))
		{
			return;
		}
		m_nHead = 0;
		m_nTail = 1;
		return;
	}
	if (m_nHead == 0)
	{
		// TODO
	}
	else
	{
		m_tArray[--m_nHead] = t;
	}
}

template <typename T>
void CsVector<T>::PopBack()
{
	if (!Valid())
	{
		return;
	}
	m_nTail--; // i = (m_nTail--) - 1;
}

template <typename T>
void CsVector<T>::PopFront()
{
	if (!Valid())
	{
		return;
	}
	m_nHead++; // i = m_nHead++;
}

template <typename T>
cs_size_t CsVector<T>::MemSize() const
{
	return m_tArray.Length();
}

template <typename T>
cs_bool CsVector<T>::Valid() const
{
	return m_nHead >= 0 
		&& m_nTail > m_nHead 
		&& m_nTail <= MemSize();
}

template <typename T>
size_t RealID(const size_t i) const
{
	return m_nHead + i;
}

#endif // _CSCORE_VECTOR_H_

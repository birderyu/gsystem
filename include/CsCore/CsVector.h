#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "CsDynamicArray.h"

#define CS_DEFAULT_VECTOR_SIZE			5
#define CS_DEFAULT_VECTOR_CAPACITY		0.5

template <typename T>
class CsVector 
	: public CsObject
{
public:
	class Iterator
	{
	public:
		inline Iterator() : i(NULL) {}
		inline Iterator(T *n) : i(n) {}

		inline T &operator*() const { return *i; }
		inline T *operator->() const { return i; }
		inline T &operator[](int j) const { return *(i + j); }
		inline bool operator==(const Iterator &o) const { return i == o.i; }
		inline bool operator!=(const Iterator &o) const { return i != o.i; }
		inline bool operator<(const Iterator& other) const { return i < other.i; }
		inline bool operator<=(const Iterator& other) const { return i <= other.i; }
		inline bool operator>(const Iterator& other) const { return i > other.i; }
		inline bool operator>=(const Iterator& other) const { return i >= other.i; }
		inline Iterator &operator++() { ++i; return *this; }
		inline Iterator operator++(int) { T *n = i; ++i; return n; }
		inline Iterator &operator--() { i--; return *this; }
		inline Iterator operator--(int) { T *n = i; i--; return n; }
		inline Iterator &operator+=(int j) { i += j; return *this; }
		inline Iterator &operator-=(int j) { i -= j; return *this; }
		inline Iterator operator+(int j) const { return Iterator(i + j); }
		inline Iterator operator-(int j) const { return Iterator(i - j); }
		inline int operator-(Iterator j) const { return i - j.i; }
		inline operator T*() const { return i; }

	private:
		T *i;
	};

	class ConstIterator
	{
	public:
		inline ConstIterator() : i(0) {}
		inline ConstIterator(const T *n) : i(n) {}
		
		inline explicit ConstIterator(const Iterator &o) : i(o.i) {}
		inline const T &operator*() const { return *i; }
		inline const T *operator->() const { return i; }
		inline const T &operator[](int j) const { return *(i + j); }
		inline bool operator==(const ConstIterator &o) const { return i == o.i; }
		inline bool operator!=(const ConstIterator &o) const { return i != o.i; }
		inline bool operator<(const ConstIterator& other) const { return i < other.i; }
		inline bool operator<=(const ConstIterator& other) const { return i <= other.i; }
		inline bool operator>(const ConstIterator& other) const { return i > other.i; }
		inline bool operator>=(const ConstIterator& other) const { return i >= other.i; }
		inline ConstIterator &operator++() { ++i; return *this; }
		inline ConstIterator operator++(int) { const T *n = i; ++i; return n; }
		inline ConstIterator &operator--() { i--; return *this; }
		inline ConstIterator operator--(int) { const T *n = i; i--; return n; }
		inline ConstIterator &operator+=(int j) { i += j; return *this; }
		inline ConstIterator &operator-=(int j) { i -= j; return *this; }
		inline ConstIterator operator+(int j) const { return ConstIterator(i + j); }
		inline ConstIterator operator-(int j) const { return ConstIterator(i - j); }
		inline int operator-(ConstIterator j) const { return i - j.i; }
		inline operator const T*() const { return i; }

	private:
		const T *i;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	CsVector();
	explicit CsVector(const cs_size_t len, const &T t = T());
	cs_bool Reserve(const cs_size_t len) const;
	cs_bool Resize(const cs_size_t len) const;

	cs_size_t Length() const;
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

	CsDynamicArray<T> m_tArray;

	// 头指针，指向首元素，初始值为-1
	cs_int m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为-1
	cs_int m_nTail;
};

template <typename T>
CsVector<T>::CsVector()
:CsDynamicArray(), m_nHead(-1), m_nTail(-1)
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
	CsDynamicArray tArray(len);

}

template <typename T>
cs_bool CsVector<T>::Resize(const cs_size_t len) const
{

}

template <typename T>
cs_size_t CsVector<T>::Length() const
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
	return Length() == 0;
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
	return m_tArray.Size();
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

#endif // _CORE_VECTOR_H_
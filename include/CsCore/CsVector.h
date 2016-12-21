#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "CsDynamicArray.h"

template <typename DataT>
class CsVector 
	: CsListT<CsVector<DataT>>
	, public CsObject
{
public:
	class Iterator
	{
	public:
		inline Iterator() : i(NULL) {}
		inline Iterator(DataT *n) : i(n) {}

		inline DataT &operator*() const { return *i; }
		inline DataT *operator->() const { return i; }
		inline DataT &operator[](int j) const { return *(i + j); }
		inline bool operator==(const Iterator &o) const { return i == o.i; }
		inline bool operator!=(const Iterator &o) const { return i != o.i; }
		inline bool operator<(const Iterator& other) const { return i < other.i; }
		inline bool operator<=(const Iterator& other) const { return i <= other.i; }
		inline bool operator>(const Iterator& other) const { return i > other.i; }
		inline bool operator>=(const Iterator& other) const { return i >= other.i; }
		inline Iterator &operator++() { ++i; return *this; }
		inline Iterator operator++(int) { DataT *n = i; ++i; return n; }
		inline Iterator &operator--() { i--; return *this; }
		inline Iterator operator--(int) { DataT *n = i; i--; return n; }
		inline Iterator &operator+=(int j) { i += j; return *this; }
		inline Iterator &operator-=(int j) { i -= j; return *this; }
		inline Iterator operator+(int j) const { return Iterator(i + j); }
		inline Iterator operator-(int j) const { return Iterator(i - j); }
		inline cs_int operator-(Iterator j) const { return i - j.i; }
		inline operator DataT*() const { return i; }

	private:
		DataT *i;
	};

	class ConstIterator
	{
	public:
		inline ConstIterator() : i(0) {}
		inline ConstIterator(const DataT *n) : i(n) {}
		
		inline explicit ConstIterator(const Iterator &o) : i(o.i) {}
		inline const DataT &operator*() const { return *i; }
		inline const DataT *operator->() const { return i; }
		inline const DataT &operator[](int j) const { return *(i + j); }
		inline cs_bool operator==(const ConstIterator &o) const { return i == o.i; }
		inline cs_bool operator!=(const ConstIterator &o) const { return i != o.i; }
		inline cs_bool operator<(const ConstIterator& other) const { return i < other.i; }
		inline cs_bool operator<=(const ConstIterator& other) const { return i <= other.i; }
		inline cs_bool operator>(const ConstIterator& other) const { return i > other.i; }
		inline cs_bool operator>=(const ConstIterator& other) const { return i >= other.i; }
		inline ConstIterator &operator++() { ++i; return *this; }
		inline ConstIterator operator++(int) { const DataT *n = i; ++i; return n; }
		inline ConstIterator &operator--() { i--; return *this; }
		inline ConstIterator operator--(int) { const DataT *n = i; i--; return n; }
		inline ConstIterator &operator+=(int j) { i += j; return *this; }
		inline ConstIterator &operator-=(int j) { i -= j; return *this; }
		inline ConstIterator operator+(int j) const { return ConstIterator(i + j); }
		inline ConstIterator operator-(int j) const { return ConstIterator(i - j); }
		inline int operator-(ConstIterator j) const { return i - j.i; }
		inline operator const DataT*() const { return i; }

	private:
		const DataT *i;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	CsVector();
	explicit CsVector(cs_size_t size, const DataT &data = DataT());
	cs_bool Reserve(cs_size_t size) const;
	cs_bool Resize(cs_size_t size) const;

	cs_size_t Size() const;
	cs_size_t Capacity() const;
	cs_bool IsEmpty() const;
	cs_void Clear();

	DataT &GetAt(cs_size_t);
	DataT  GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	DataT  operator[](cs_size_t) const;

	cs_void PushBack(const DataT &data);
	cs_void PushFront(const DataT &data);
	cs_void PopBack(DataT *data = NULL);
	cs_void PopFront(DataT *data = NULL);

private:
	cs_size_t RealPos(cs_size_t pos) const;
	cs_bool Valid() const;

	// 动态数组
	CsDynamicArray<DataT> m_tArray;

	// 头指针，指向首元素，初始值为NULL_POS
	cs_size_t m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为0
	cs_size_t m_nTail;
};

template <typename DataT>
CsVector<DataT>::CsVector()
: m_tArray(1), m_nHead(NULL_POS), m_nTail(0)
{

}

template <typename DataT>
CsVector<DataT>::CsVector(cs_size_t size, const DataT &data)
: m_tArray(size, data), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
cs_bool CsVector<DataT>::Reserve(cs_size_t size) const
{
	if (size <= Capacity())
	{
		// 无需扩容
		return true;
	}
	if (!m_tArray.Resize(size))
	{
		return false;
	}
	return true;
}

template <typename DataT>
cs_bool CsVector<DataT>::Resize(cs_size_t size) const
{
	if (size <= Size())
	{
		return true;
	}
	if (size > Capacity())
	{
		if (!Reserve(size))
		{
			return false;
		}
	}
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	m_nTail = size - m_nHead;
	return true;
}

template <typename DataT>
cs_size_t CsVector<DataT>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename DataT>
cs_size_t CsVector<DataT>::Capacity() const
{
	cs_size_t arr_size = m_tArray.Size();
	if (m_nHead == NULL_POS)
	{
		return arr_size;
	}
	CS_ASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename DataT>
cs_bool CsVector<DataT>::IsEmpty() const
{
	return Size() == 0;
}

template <typename DataT>
cs_size_t CsVector<DataT>::RealPos(cs_size_t pos) const
{
	if (m_pHead == NULL_POS)
	{
		return NULL_POS;
	}
	return m_nHead + pos;
}

template <typename DataT>
cs_bool CsVector<DataT>::Valid() const
{
	return m_nHead != NULL_POS
		&& m_nTail != NULL_POS
		&& m_nTail > m_nHead 
		&& m_nTail <= m_tArray.Size();
}

template <typename DataT>
cs_void CsVector<DataT>::Clear()
{
	m_nHead = m_nTail = NULL_POS;
}

template <typename DataT>
DataT &CsVector<DataT>::GetAt(cs_size_t pos)
{
	cs_size_t real_pos = RealPos(pos);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
DataT CsVector<DataT>::GetAt(cs_size_t pos) const
{
	cs_size_t real_pos = RealPos(pos);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
DataT &CsVector<DataT>::operator[](cs_size_t pos)
{
	cs_size_t real_pos = RealPos(pos);
	return m_tArray[real_pos];
}

template <typename DataT>
DataT CsVector<DataT>::operator[](cs_size_t pos) const
{
	cs_size_t real_pos = RealPos(pos);
	return m_tArray[real_pos];
}

template <typename DataT>
cs_void CsVector<DataT>::PushBack(const DataT &data)
{
	cs_size_t old_capacity = Capacity();
	if (Size() >= old_capacity)
	{
		Reserve(old_capacity / 2 + 1);
	}
	m_tArray[m_nTail++] = data;
}

template <typename DataT>
cs_void CsVector<DataT>::PushFront(const DataT &data)
{
	if (m_nHead > 0)
	{
		m_tArray[m_nHead--] = data;
		return;
	}
	
}

template <typename DataT>
cs_void CsVector<DataT>::PopBack(DataT *data)
{
	if (!Valid())
	{

	}
}

template <typename DataT>
cs_void CsVector<DataT>::PopFront(DataT *data)
{

}

#endif // _CORE_VECTOR_H_
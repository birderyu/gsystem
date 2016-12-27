// 使用动态数组实现
#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "CsDynamicArray.h"

#define CS_VECTOR_DEFAULT_CAPACITY 16

template <typename DataT>
class CsVector final
	: CsListT<CsVector<DataT>>
	, public CsObject
{
public:
	class Iterator
	{
	public:
		inline Iterator() : m_pData(NULL) {}
		inline Iterator(DataT *data) : m_pData(data) {}
		inline explicit Iterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		inline DataT &operator*() const { return *m_pData; }
		inline DataT *operator->() const { return m_pData; }
		inline DataT &operator[](cs_size_t pos) const { return *(m_pData + pos); }
		inline bool operator==(const Iterator &iter) const { return m_pData == iter.m_pData; }
		inline bool operator!=(const Iterator &iter) const { return m_pData != iter.m_pData; }
		inline bool operator<(const Iterator &iter) const { return m_pData < iter.m_pData; }
		inline bool operator<=(const Iterator &iter) const { return m_pData <= iter.m_pData; }
		inline bool operator>(const Iterator &iter) const { return m_pData > iter.m_pData; }
		inline bool operator>=(const Iterator &iter) const { return m_pData >= iter.m_pData; }
		inline Iterator &operator++() { ++m_pData; return *this; }
		inline Iterator  operator++(cs_int) { DataT *data = m_pData; ++m_pData; return data; }
		inline Iterator &operator--() { m_pData--; return *this; }
		inline Iterator  operator--(cs_int) { DataT *data = m_pData; m_pData--; return data; }
		inline Iterator &operator+=(cs_int i) { m_pData += i; return *this; }
		inline Iterator &operator-=(cs_int i) { m_pData -= i; return *this; }
		inline Iterator  operator+(cs_int i) const { return Iterator(m_pData + i); }
		inline Iterator  operator-(cs_int i) const { return Iterator(m_pData - i); }
		inline cs_int operator-(const Iterator &iter) const { return m_pData - iter.m_pData; }
		inline operator DataT*() const { return m_pData; }

	private:
		DataT *m_pData;
	};

	class ConstIterator
	{
	public:
		inline ConstIterator() : m_pData(NULL) {}
		inline ConstIterator(const DataT *data) : m_pData(data) {}
		inline explicit ConstIterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		inline const DataT &operator*() const { return *m_pData; }
		inline const DataT *operator->() const { return m_pData; }
		inline const DataT &operator[](cs_size_t pos) const { return *(m_pData + pos); }
		inline cs_bool operator==(const ConstIterator &citer) const { return m_pData == citer.m_pData; }
		inline cs_bool operator!=(const ConstIterator &citer) const { return m_pData != citer.m_pData; }
		inline cs_bool operator<(const ConstIterator &citer) const { return m_pData < citer.m_pData; }
		inline cs_bool operator<=(const ConstIterator &citer) const { return m_pData <= citer.m_pData; }
		inline cs_bool operator>(const ConstIterator &citer) const { return m_pData > citer.m_pData; }
		inline cs_bool operator>=(const ConstIterator &citer) const { return m_pData >= citer.m_pData; }
		inline ConstIterator &operator++() { ++m_pData; return *this; }
		inline ConstIterator  operator++(cs_int) { const DataT *n = m_pData; ++m_pData; return n; }
		inline ConstIterator &operator--() { m_pData--; return *this; }
		inline ConstIterator  operator--(cs_int) { const DataT *data = m_pData; m_pData--; return data; }
		inline ConstIterator &operator+=(cs_int i) { m_pData += i; return *this; }
		inline ConstIterator &operator-=(cs_int i) { m_pData -= i; return *this; }
		inline ConstIterator  operator+(cs_int i) const { return ConstIterator(m_pData + i); }
		inline ConstIterator  operator-(cs_int i) const { return ConstIterator(m_pData - i); }
		inline int operator-(const ConstIterator &citer) const { return m_pData - citer.m_pData; }
		inline operator const DataT*() const { return m_pData; }

	private:
		const DataT *m_pData;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	CsVector();
	explicit CsVector(cs_size_t size);
	explicit CsVector(cs_size_t size, const DataT &data);
	CsVector(const CsVector<DataT> &);
	cs_bool Reserve(cs_size_t);
	cs_bool Resize(cs_size_t);

	cs_size_t Size() const;
	cs_size_t Capacity() const;
	cs_bool IsEmpty() const;
	cs_void Clear(); // 清空数组，不变销毁数据
	cs_void Dispose(); // 销毁所有数据
	//cs_void Collect(); // 回收垃圾

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;

	cs_void PushBack(const DataT &data);
	cs_void PushFront(const DataT &data);
	cs_void PopBack(DataT *data = NULL);
	cs_void PopBack(cs_size_t size); // 从队尾除去size个元素
	cs_void PopFront(DataT *data = NULL);
	cs_void PopFront(cs_size_t size); // 从队首除去size个元素

	cs_void	Append(const DataT &);
	cs_void	Append(const CsVector<DataT> &);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	DataT &First();
	const DataT &First() const;
	DataT &Last();
	const DataT &Last() const;

	cs_bool StartWith(const DataT &) const;
	cs_bool EndWith(const DataT &) const;

	//Iterator Erase(const Iterator &iter);
	//Iterator Erase(const Iterator &begin, const Iterator &end);

	//cs_void RemoveAt(cs_size_t);
	//cs_void Remove(cs_size_t start, cs_size_t size);
	//cs_void Remove(const DataT &);

	//cs_size_t FirstIndexOf(const DataT &);
	//cs_size_t LastIndexOf(const DataT &);

	DataT *Head();
	const DataT *Head() const;
	DataT *Tail();
	const DataT *Tail() const;

private:
	cs_size_t RealPos(cs_size_t pos) const;
	cs_bool Valid() const;
	cs_bool Reserve(cs_size_t, cs_size_t start);

	// 动态数组
	CsDynamicArray<DataT> m_tArray;

	// 头指针，指向首元素，初始值为NULL_POS
	cs_size_t m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为0
	cs_size_t m_nTail;
};

#include "CsVector.inl"

#undef CS_VECTOR_DEFAULT_CAPACITY

#endif // _CORE_VECTOR_H_
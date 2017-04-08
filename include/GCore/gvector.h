// 使用动态数组实现的顺序容器
#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "gdeque.h"
#include "gdynamicarray.h"

#define G_VECTOR_DEFAULT_CAPACITY 16

namespace gsystem { // gsystem

template <typename DataT>
class GVector final
	: public GArray<DataT>
	, public GDeque<DataT>
	, virtual public GObject
	, virtual public GSerializable
{
public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		GINLINE Iterator() : m_pData(GNULL) {}
		GINLINE Iterator(DataT *data) : m_pData(data) {}
		GINLINE explicit Iterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		GINLINE DataT &operator*() const { return *m_pData; }
		GINLINE DataT *operator->() const { return m_pData; }
		GINLINE DataT &operator[](gsize pos) const { return *(m_pData + pos); }
		GINLINE bool operator==(const Iterator &iter) const { return m_pData == iter.m_pData; }
		GINLINE bool operator!=(const Iterator &iter) const { return m_pData != iter.m_pData; }
		GINLINE bool operator<(const Iterator &iter) const { return m_pData < iter.m_pData; }
		GINLINE bool operator<=(const Iterator &iter) const { return m_pData <= iter.m_pData; }
		GINLINE bool operator>(const Iterator &iter) const { return m_pData > iter.m_pData; }
		GINLINE bool operator>=(const Iterator &iter) const { return m_pData >= iter.m_pData; }
		GINLINE Iterator &operator++() { ++m_pData; return *this; }
		GINLINE Iterator  operator++(gint) { DataT *data = m_pData; ++m_pData; return data; }
		GINLINE Iterator &operator--() { m_pData--; return *this; }
		GINLINE Iterator  operator--(gint) { DataT *data = m_pData; m_pData--; return data; }
		GINLINE Iterator &operator+=(gint i) { m_pData += i; return *this; }
		GINLINE Iterator &operator-=(gint i) { m_pData -= i; return *this; }
		GINLINE Iterator  operator+(gint i) const { return Iterator(m_pData + i); }
		GINLINE Iterator  operator-(gint i) const { return Iterator(m_pData - i); }
		GINLINE gint operator-(const Iterator &iter) const { return m_pData - iter.m_pData; }
		GINLINE operator DataT*() const { return m_pData; }

	private:
		DataT *m_pData;
	};

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pData(GNULL) {}
		GINLINE ConstIterator(const DataT *data) : m_pData(data) {}
		GINLINE explicit ConstIterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		GINLINE const DataT &operator*() const { return *m_pData; }
		GINLINE const DataT *operator->() const { return m_pData; }
		GINLINE const DataT &operator[](gsize pos) const { return *(m_pData + pos); }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pData == citer.m_pData; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pData != citer.m_pData; }
		GINLINE gbool operator<(const ConstIterator &citer) const { return m_pData < citer.m_pData; }
		GINLINE gbool operator<=(const ConstIterator &citer) const { return m_pData <= citer.m_pData; }
		GINLINE gbool operator>(const ConstIterator &citer) const { return m_pData > citer.m_pData; }
		GINLINE gbool operator>=(const ConstIterator &citer) const { return m_pData >= citer.m_pData; }
		GINLINE ConstIterator &operator++() { ++m_pData; return *this; }
		GINLINE ConstIterator  operator++(gint) { const DataT *n = m_pData; ++m_pData; return n; }
		GINLINE ConstIterator &operator--() { m_pData--; return *this; }
		GINLINE ConstIterator  operator--(gint) { const DataT *data = m_pData; m_pData--; return data; }
		GINLINE ConstIterator &operator+=(gint i) { m_pData += i; return *this; }
		GINLINE ConstIterator &operator-=(gint i) { m_pData -= i; return *this; }
		GINLINE ConstIterator  operator+(gint i) const { return ConstIterator(m_pData + i); }
		GINLINE ConstIterator  operator-(gint i) const { return ConstIterator(m_pData - i); }
		GINLINE int operator-(const ConstIterator &citer) const { return m_pData - citer.m_pData; }
		GINLINE operator const DataT*() const { return m_pData; }

	private:
		const DataT *m_pData;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GVector();
	explicit GVector(gsize size);
	explicit GVector(gsize size, const DataT &data);
	GVector(const GVector<DataT> &);
	GVector(GVector<DataT> &&);

	GVector<DataT> &operator=(const GVector<DataT> &);
	GVector<DataT> &operator=(GVector<DataT> &&);

	gvoid Reserve(gsize);
	gvoid Resize(gsize);

	gsize Size() const;
	gsize Capacity() const;
	gbool IsEmpty() const;
	gvoid Clear(); // 清空数组，不变销毁数据
	gvoid Destroy(); // 销毁所有数据
	//gvoid Collect(); // 回收垃圾

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT *CursorAt(gsize);
	const DataT *CursorAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

	gvoid PushBack(const DataT &data);
	gvoid PushBack(DataT &&data);

	gvoid PushFront(const DataT &data);
	gvoid PushFront(DataT &&data);

	gvoid PopBack(DataT *data = GNULL);
	gvoid PopBack(gsize size); // 从队尾除去size个元素，这些元素会全部被析构

	gvoid PopFront(DataT *data = GNULL);
	gvoid PopFront(gsize size); // 从队首除去size个元素，这些元素会全部被析构

	gvoid Append(const DataT &data);
	gvoid Append(DataT &&data);

	gvoid Append(const GVector<DataT> &arr);
	gvoid Append(GVector<DataT> &&arr);

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

	gbool StartWith(const DataT &) const;
	gbool EndWith(const DataT &) const;

	//Iterator Erase(const Iterator &iter);
	//Iterator Erase(const Iterator &begin, const Iterator &end);

	gvoid RemoveAt(gsize pos);
	//gvoid Remove(gsize start, gsize size);
	//gvoid Remove(const DataT &);
	//gsize FirstIndexOf(const DataT &);
	//gsize LastIndexOf(const DataT &);

	DataT *Head();
	const DataT *Head() const;
	DataT *Tail();
	const DataT *Tail() const;

	//gvoid MemCopyFrom(const GVector<DataT> &);

	guint ClassCode() const;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	gsize RealPos(gsize pos) const;
	gbool Valid() const;
	gvoid Reserve(gsize, gsize start);

	// 动态数组
	GDynamicArray<DataT> m_tArray;

	// 头指针，指向首元素，初始值为NULL_POS
	gsize m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为0
	gsize m_nTail;
};

} // namespace gsystem

#include "gvector.inl"

#undef G_VECTOR_DEFAULT_CAPACITY

#endif // _CORE_VECTOR_H_
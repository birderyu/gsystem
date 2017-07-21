// 使用动态数组实现的顺序容器
#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "gdeque.h"
#include "gdynamicarray.h"

#define G_VECTOR_DEFAULT_CAPACITY 16

namespace gsystem { // gsystem

template <typename T>
class GVector final
	: public GArray<T>
	, public GDeque<T>
	, public GSerializable
{
public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		GINLINE Iterator() : m_pData(GNULL) {}
		GINLINE Iterator(T *data) : m_pData(data) {}
		GINLINE explicit Iterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		GINLINE T &operator*() const { return *m_pData; }
		GINLINE T *operator->() const { return m_pData; }
		GINLINE T &operator[](gsize pos) const { return *(m_pData + pos); }
		GINLINE bool operator==(const Iterator &iter) const { return m_pData == iter.m_pData; }
		GINLINE bool operator!=(const Iterator &iter) const { return m_pData != iter.m_pData; }
		GINLINE bool operator<(const Iterator &iter) const { return m_pData < iter.m_pData; }
		GINLINE bool operator<=(const Iterator &iter) const { return m_pData <= iter.m_pData; }
		GINLINE bool operator>(const Iterator &iter) const { return m_pData > iter.m_pData; }
		GINLINE bool operator>=(const Iterator &iter) const { return m_pData >= iter.m_pData; }
		GINLINE Iterator &operator++() { ++m_pData; return *this; }
		GINLINE Iterator  operator++(gint) { T *data = m_pData; ++m_pData; return data; }
		GINLINE Iterator &operator--() { m_pData--; return *this; }
		GINLINE Iterator  operator--(gint) { T *data = m_pData; m_pData--; return data; }
		GINLINE Iterator &operator+=(gint i) { m_pData += i; return *this; }
		GINLINE Iterator &operator-=(gint i) { m_pData -= i; return *this; }
		GINLINE Iterator  operator+(gint i) const { return Iterator(m_pData + i); }
		GINLINE Iterator  operator-(gint i) const { return Iterator(m_pData - i); }
		GINLINE gint operator-(const Iterator &iter) const { return m_pData - iter.m_pData; }
		GINLINE operator T*() const { return m_pData; }

	private:
		T *m_pData;
	};

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pData(GNULL) {}
		GINLINE ConstIterator(const T *data) : m_pData(data) {}
		GINLINE explicit ConstIterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		GINLINE const T &operator*() const { return *m_pData; }
		GINLINE const T *operator->() const { return m_pData; }
		GINLINE const T &operator[](gsize pos) const { return *(m_pData + pos); }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pData == citer.m_pData; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pData != citer.m_pData; }
		GINLINE gbool operator<(const ConstIterator &citer) const { return m_pData < citer.m_pData; }
		GINLINE gbool operator<=(const ConstIterator &citer) const { return m_pData <= citer.m_pData; }
		GINLINE gbool operator>(const ConstIterator &citer) const { return m_pData > citer.m_pData; }
		GINLINE gbool operator>=(const ConstIterator &citer) const { return m_pData >= citer.m_pData; }
		GINLINE ConstIterator &operator++() { ++m_pData; return *this; }
		GINLINE ConstIterator  operator++(gint) { const T *n = m_pData; ++m_pData; return n; }
		GINLINE ConstIterator &operator--() { m_pData--; return *this; }
		GINLINE ConstIterator  operator--(gint) { const T *data = m_pData; m_pData--; return data; }
		GINLINE ConstIterator &operator+=(gint i) { m_pData += i; return *this; }
		GINLINE ConstIterator &operator-=(gint i) { m_pData -= i; return *this; }
		GINLINE ConstIterator  operator+(gint i) const { return ConstIterator(m_pData + i); }
		GINLINE ConstIterator  operator-(gint i) const { return ConstIterator(m_pData - i); }
		GINLINE int operator-(const ConstIterator &citer) const { return m_pData - citer.m_pData; }
		GINLINE operator const T*() const { return m_pData; }

	private:
		const T *m_pData;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GVector();
	explicit GVector(gsize size);
	explicit GVector(gsize size, const T &data);
	GVector(const GVector<T> &);
	GVector(GVector<T> &&);

	GVector<T> &operator=(const GVector<T> &);
	GVector<T> &operator=(GVector<T> &&);

	gvoid Reserve(gsize);
	gvoid Resize(gsize);

	gsize Size() const;
	gsize Capacity() const;
	gbool IsEmpty() const;
	gvoid Clear(); // 清空数组，不变销毁数据
	gvoid Destroy(); // 销毁所有数据
	//gvoid Collect(); // 回收垃圾

	T &GetAt(gsize);
	const T &GetAt(gsize) const;

	T *CursorAt(gsize);
	const T *CursorAt(gsize) const;

	T &operator[](gsize);
	const T &operator[](gsize) const;

	gvoid PushBack(const T &data);
	gvoid PushBack(T &&data);

	gvoid PushFront(const T &data);
	gvoid PushFront(T &&data);

	gvoid PopBack(T *data = GNULL);
	gvoid PopBack(gsize size); // 从队尾除去size个元素，这些元素会全部被析构

	gvoid PopFront(T *data = GNULL);
	gvoid PopFront(gsize size); // 从队首除去size个元素，这些元素会全部被析构

	gvoid Append(const T &data);
	gvoid Append(T &&data);

	gvoid Append(const GVector<T> &arr);
	gvoid Append(GVector<T> &&arr);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	T &First();
	const T &First() const;
	T &Last();
	const T &Last() const;

	gbool StartWith(const T &) const;
	gbool EndWith(const T &) const;

	//Iterator Erase(const Iterator &iter);
	//Iterator Erase(const Iterator &begin, const Iterator &end);

	gvoid RemoveAt(gsize pos);
	//gvoid Remove(gsize start, gsize size);
	//gvoid Remove(const T &);
	//gsize FirstIndexOf(const T &);
	//gsize LastIndexOf(const T &);

	T *Head();
	const T *Head() const;
	T *Tail();
	const T *Tail() const;

	//gvoid MemCopyFrom(const GVector<T> &);

	guint ClassCode() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	gsize RealPos(gsize pos) const;
	gbool Valid() const;
	gvoid Reserve(gsize, gsize start);

	// 动态数组
	GDynamicArray<T> m_tArray;

	// 头指针，指向首元素，初始值为NULL_POS
	gsize m_nHead;

	// 尾指针，指向末尾元素的下一位，初始值为0
	gsize m_nTail;
};

} // namespace gsystem

#include "inline/gvector.inl"

#undef G_VECTOR_DEFAULT_CAPACITY

#endif // _CORE_VECTOR_H_
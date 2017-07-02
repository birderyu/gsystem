// 使用数组表示的二叉堆
#ifndef _CORE_BINARY_HEAP_H_
#define _CORE_BINARY_HEAP_H_

#include "gdynamicarray.h"
#include "gfunctor.h"

#define G_BINARY_HEAP_DEFAULT_CAPACITY 1024
#define G_BINARY_HEAP_DEFAULT_ADD_SIZE 512

namespace gsystem { // gsystem

template<typename DataT, typename CompareT>
class GBinHeap
	: public GListT<GBinHeap<DataT, CompareT>>
	, public GObject
{
public:
	GBinHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinHeap(const GArray<DataT> &arr, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinHeap(DataT *arr, gsize arr_len, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinHeap(const GBinHeap<DataT, CompareT> &heap);
	GBinHeap(GBinHeap<DataT, CompareT> &&heap);

	GBinHeap<DataT, CompareT> &operator=(const GBinHeap<DataT, CompareT> &heap);
	GBinHeap<DataT, CompareT> &operator=(GBinHeap<DataT, CompareT> &&heap);

	gvoid Append(const GArray<DataT> &arr);
	gvoid Append(const GArray<DataT> &arr, gsize start, gsize size);
	gvoid Append(DataT *arr, gsize arr_size);
	gvoid Append(DataT *arr, gsize start, gsize size);
	gvoid Append(const GBinHeap<DataT, CompareT> &);
	gvoid Append(const GBinHeap<DataT, CompareT> &heap, gsize start, gsize size);

	// 模板添加方法，可以添加任何有数组行为的类
	template<typename ArrT> gvoid AppendT(const ArrT &arr);
	template<typename ArrT> gvoid AppendT(const ArrT &arr, gsize start, gsize size);

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gvoid Reserve(gsize);

	gvoid Insert(const DataT &data);
	gbool Pop(DataT *data = GNULL);
	DataT Top() const;

	gvoid Output() const;

private:
	GDynamicArray<DataT> m_tHeap;
	gsize m_nSize;
	gsize m_nAddSize;
	static CompareT m_fCompare;
};

template<typename DataT>
class GMinHeap
	: public GBinHeap<DataT, GLessThanF<DataT>>
{
public:
	GMinHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GLessThanF<DataT>>(capacity, add_size)
	{

	}

	GMinHeap(const GArray<DataT> &arr,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GLessThanF<DataT>>(arr, add_size)
	{

	}

	GMinHeap(DataT *arr, gsize arr_len,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GLessThanF<DataT>>(arr, arr_len, add_size)
	{

	}

	GMinHeap(const GMinHeap<DataT> &heap)
		: GBinHeap<DataT, GLessThanF<DataT>>(heap)
	{

	}

	GMinHeap(GMinHeap<DataT> &&heap)
		: GBinHeap<DataT, GLessThanF<DataT>>(GForward<GMinHeap<DataT>>(heap))
	{

	}
};

template<typename DataT>
class GMaxHeap
	: public GBinHeap<DataT, GGreaterThanF<DataT>>
{
public:
	GMaxHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GGreaterThanF<DataT>>(capacity, add_size)
	{

	}

	GMaxHeap(const GArray<DataT> &arr,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GGreaterThanF<DataT>>(arr, add_size)
	{

	}

	GMaxHeap(DataT *arr, gsize arr_len,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinHeap<DataT, GGreaterThanF<DataT>>(arr, arr_len, add_size)
	{

	}

	GMaxHeap(const GMaxHeap<DataT> &heap)
		: GBinHeap<DataT, GGreaterThanF<DataT>>(heap)
	{

	}

	GMaxHeap(GMaxHeap<DataT> &&heap)
		: GBinHeap<DataT, GGreaterThanF<DataT>>(GForward<GMaxHeap<DataT>>(heap))
	{

	}
};

} // namespace gsystem

#include "inline/gbinheap.inl"

#undef G_BINARY_HEAP_DEFAULT_ADD_SIZE
#undef G_BINARY_HEAP_DEFAULT_CAPACITY

#endif // _CORE_BINARY_HEAP_H_
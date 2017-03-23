// 使用数组表示的二叉堆
#ifndef _CORE_BINARY_HEAP_H_
#define _CORE_BINARY_HEAP_H_

#include "gdynamicarray.h"
#include "gfunctor.h"

#define G_BINARY_HEAP_DEFAULT_CAPACITY 1024
#define G_BINARY_HEAP_DEFAULT_ADD_SIZE 512

namespace gsystem { // gsystem

template<typename DataT, typename CompareT>
class GBinaryHeap
	: public GListT<GBinaryHeap<DataT, CompareT>>
	, public GObject
{
public:
	GBinaryHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinaryHeap(const GArray<DataT> &arr, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinaryHeap(DataT *arr, gsize arr_len, 
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE);
	GBinaryHeap(const GBinaryHeap<DataT, CompareT> &heap);
	GBinaryHeap(GBinaryHeap<DataT, CompareT> &&heap);

	GBinaryHeap<DataT, CompareT> &operator=(const GBinaryHeap<DataT, CompareT> &heap);
	GBinaryHeap<DataT, CompareT> &operator=(GBinaryHeap<DataT, CompareT> &&heap);

	gvoid Append(const GArray<DataT> &arr);
	gvoid Append(const GArray<DataT> &arr, gsize start, gsize size);
	gvoid Append(DataT *arr, gsize arr_size);
	gvoid Append(DataT *arr, gsize start, gsize size);
	gvoid Append(const GBinaryHeap<DataT, CompareT> &);
	gvoid Append(const GBinaryHeap<DataT, CompareT> &heap, gsize start, gsize size);

	// 模板添加方法，可以添加任何有数组行为的类
	template<typename ArrT> gvoid AppendT(const ArrT &arr);
	template<typename ArrT> gvoid AppendT(const ArrT &arr, gsize start, gsize size);

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbool Reserve(gsize);

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
	: public GBinaryHeap<DataT, GLessThanF<DataT>>
{
public:
	GMinHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GLessThanF<DataT>>(capacity, add_size)
	{

	}

	GMinHeap(const GArray<DataT> &arr,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GLessThanF<DataT>>(arr, add_size)
	{

	}

	GMinHeap(DataT *arr, gsize arr_len,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GLessThanF<DataT>>(arr, arr_len, add_size)
	{

	}

	GMinHeap(const GMinHeap<DataT> &heap)
		: GBinaryHeap<DataT, GLessThanF<DataT>>(heap)
	{

	}

	GMinHeap(GMinHeap<DataT> &&heap)
		: GBinaryHeap<DataT, GLessThanF<DataT>>(GForward<GMinHeap<DataT>>(heap))
	{

	}
};

template<typename DataT>
class GMaxHeap
	: public GBinaryHeap<DataT, GGreaterThanF<DataT>>
{
public:
	GMaxHeap(gsize capacity = G_BINARY_HEAP_DEFAULT_CAPACITY,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GGreaterThanF<DataT>>(capacity, add_size)
	{

	}

	GMaxHeap(const GArray<DataT> &arr,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GGreaterThanF<DataT>>(arr, add_size)
	{

	}

	GMaxHeap(DataT *arr, gsize arr_len,
		gsize add_size = G_BINARY_HEAP_DEFAULT_ADD_SIZE)
		: GBinaryHeap<DataT, GGreaterThanF<DataT>>(arr, arr_len, add_size)
	{

	}

	GMaxHeap(const GMaxHeap<DataT> &heap)
		: GBinaryHeap<DataT, GGreaterThanF<DataT>>(heap)
	{

	}

	GMaxHeap(GMaxHeap<DataT> &&heap)
		: GBinaryHeap<DataT, GGreaterThanF<DataT>>(GForward<GMaxHeap<DataT>>(heap))
	{

	}
};

} // namespace gsystem

#include "gbinaryheap.inl"

#undef G_BINARY_HEAP_DEFAULT_ADD_SIZE
#undef G_BINARY_HEAP_DEFAULT_CAPACITY

#endif // _CORE_BINARY_HEAP_H_
// 使用数组表示的二叉堆
#ifndef _CORE_BINARY_HEAP_H_
#define _CORE_BINARY_HEAP_H_

#include "CsObject.h"
#include "CsDynamicArray.h"

#define CS_HEAP_DEFAULT_CAPACITY 1024
#define CS_HEAP_DEFAULT_ADD_SIZE 512

template<typename DataT, typename CompareT>
class CsBinaryHeap
	: public CsListT<CsBinaryHeap<DataT, CompareT>>
	, public CsObject
{
public:
	CsBinaryHeap(cs_size_t capacity = CS_HEAP_DEFAULT_CAPACITY, 
		cs_size_t add_size = CS_HEAP_DEFAULT_ADD_SIZE);
	CsBinaryHeap(const CsArray<DataT> &arr, 
		cs_size_t add_size = CS_HEAP_DEFAULT_ADD_SIZE);
	CsBinaryHeap(DataT *arr, cs_size_t arr_len, 
		cs_size_t add_size = CS_HEAP_DEFAULT_ADD_SIZE);
	CsBinaryHeap(const CsBinaryHeap<DataT, CompareT> &heap);

	cs_void Append(const CsArray<DataT> &arr);
	cs_void Append(const CsArray<DataT> &arr, cs_size_t start, cs_size_t size);
	cs_void Append(DataT *arr, cs_size_t arr_size);
	cs_void Append(DataT *arr, cs_size_t start, cs_size_t size);
	cs_void Append(const CsBinaryHeap<DataT, CompareT> &);
	cs_void Append(const CsBinaryHeap<DataT, CompareT> &heap, cs_size_t start, cs_size_t size);

	// 模板添加方法，可以添加任何有数组行为的类
	template<typename ArrT>cs_void AppendT(const ArrT &arr);
	template<typename ArrT>cs_void AppendT(const ArrT &arr, cs_size_t start, cs_size_t size);

	cs_size_t Size() const;
	cs_size_t Capacity() const;

	cs_bool Reserve(cs_size_t);

	cs_void Insert(const DataT &data);
	cs_bool Pop(DataT *data = NULL);
	cs_bool Top(DataT &data) const;

	cs_void Output() const;

private:
	CsDynamicArray<DataT> m_tHeap;
	cs_size_t m_nSize;
	cs_size_t m_nAddSize;
	CompareT m_fCompare;
};

template<typename DataT>
class CsMinHeap
	: public CsBinaryHeap<DataT, CsLessThanF<DataT>>
{

};

template<typename DataT>
class CsMaxHeap
	: public CsBinaryHeap<DataT, CsGreaterThanF<DataT>>
{

};

#include "CsBinaryHeap.inl"

#undef CS_HEAP_DEFAULT_ADD_SIZE
#undef CS_HEAP_DEFAULT_CAPACITY

#endif // _CORE_BINARY_HEAP_H_
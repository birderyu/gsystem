#ifndef _CORE_SORT_H_
#define _CORE_SORT_H_

#include "CsGlobal.h"

/// ArrT必须提供下标操作元素的方法
/// ElemT默认情况下需实现拷贝构造和等号重载的方法，也可以通过继承仿函数CompareT的方式
/// arr：待排序的数组
/// start：待排序的数组起始位置
/// len：待排序的数组长度，注意为从start位开始的数组长度
class CS_API CsSort
{
public:
	/// 冒泡排序
	template<typename ArrT, 
		typename ElemT, 
		typename CompareT = CsLessThanF<ElemT >>
	static void BubbleSort(ArrT &arr, cs_size_t start, cs_size_t len);

	/// 插入排序
	/// bRecur：是否采用递归实现，默认不使用
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void InsertSort(ArrT &arr, cs_size_t start, cs_size_t len, cs_bool bRecur = false);

	/// 希尔排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void ShellSort(ArrT &arr, cs_size_t start, cs_size_t len);

	/// 选择排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void SelectSort(ArrT &arr, cs_size_t start, cs_size_t len);

	/// 堆排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void HeapSort(ArrT &arr, cs_size_t start, cs_size_t len);

	/// 归并排序（算法有误）
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void MergeSort(ArrT &arr, cs_size_t start, cs_size_t len);

	/// 快速排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLessThanF<ElemT >>
	static void QuickSort(ArrT &arr, cs_size_t start, cs_size_t len);
};

/// 排序算法实现类
class CsSort_Ex
{
	friend class CsSort;

private:
	/// 插入排序，递归实现（Recursive）
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void InsertSorting(ArrT &arr, const cs_size_t start, const cs_size_t len, const CompareT &compareF);

	static cs_size_t LeftChild(cs_size_t i)
	{
		return 2 * i + 1;
	}

	template<typename ElemT>
	static void Swap(ElemT* l, ElemT* r);

	/// 构建大根堆
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void PercDown(ArrT &arr, cs_size_t start, cs_size_t i, cs_size_t len, const CompareT &compareF);

	/// 归并
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void Merge(ArrT &arr, cs_size_t first, cs_size_t mid, cs_size_t last, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT,
		typename CompareT >
		static void MergeSorting(ArrT &arr, cs_size_t first, cs_size_t last, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static ElemT Median3(ArrT &arr, cs_size_t left, cs_size_t right, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT, 
		typename CompareT>
	static void QuickSorting(ArrT &arr, cs_size_t first, cs_size_t last, const CompareT &compareF);
};

#include "CsSort.inl"

#endif // _CORE_SORT_H_
#ifndef _CORE_SORT_H_
#define _CORE_SORT_H_

#include "gglobal.h"

/// ArrT必须提供下标操作元素的方法
/// ElemT默认情况下需实现拷贝构造和等号重载的方法，也可以通过继承仿函数CompareT的方式
/// arr：待排序的数组
/// start：待排序的数组起始位置
/// len：待排序的数组长度，注意为从start位开始的数组长度
class GAPI GSort
{
public:
	/// 冒泡排序
	template<typename ArrT, 
		typename ElemT, 
		typename CompareT = GLessThanF<ElemT >>
	static void BubbleSort(ArrT &arr, gsize start, gsize len);

	/// 插入排序
	/// bRecur：是否采用递归实现，默认不使用
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void InsertSort(ArrT &arr, gsize start, gsize len, gbool bRecur = false);

	/// 希尔排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void ShellSort(ArrT &arr, gsize start, gsize len);

	/// 选择排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void SelectSort(ArrT &arr, gsize start, gsize len);

	/// 堆排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void HeapSort(ArrT &arr, gsize start, gsize len);

	/// 归并排序（算法有误）
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void MergeSort(ArrT &arr, gsize start, gsize len);

	/// 快速排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = GLessThanF<ElemT >>
	static void QuickSort(ArrT &arr, gsize start, gsize len);
};

/// 排序算法实现类
class GSort_Ex
{
	friend class GSort;

private:
	/// 插入排序，递归实现（Recursive）
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void InsertSorting(ArrT &arr, const gsize start, const gsize len, const CompareT &compareF);

	static gsize LeftChild(gsize i)
	{
		return 2 * i + 1;
	}

	template<typename ElemT>
	static void Swap(ElemT* l, ElemT* r);

	/// 构建大根堆
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void PercDown(ArrT &arr, gsize start, gsize i, gsize len, const CompareT &compareF);

	/// 归并
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void Merge(ArrT &arr, gsize first, gsize mid, gsize last, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT,
		typename CompareT >
		static void MergeSorting(ArrT &arr, gsize first, gsize last, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static ElemT Median3(ArrT &arr, gsize left, gsize right, const CompareT &compareF);

	template<typename ArrT, 
		typename ElemT, 
		typename CompareT>
	static void QuickSorting(ArrT &arr, gsize first, gsize last, const CompareT &compareF);
};

#include "gsort.inl"

#endif // _CORE_SORT_H_
#ifndef _CSCORE_SORT_H_
#define _CSCORE_SORT_H_

#include "CsCoreGlobal.h"
#include "CsArray.h"

/// ArrT需下标操作元素的方法
/// ElemT需实现拷贝构造和等号重载的方法
/// arr：待排序的数组
/// start：待排序的数组起始位置
/// len：待排序的数组长度，注意为从start位开始的数组长度
class CS_CORE_EXPORT CsSort
{
public:
	/// 冒泡排序
	template<typename ArrT, 
		typename ElemT, 
		typename CompareT = CsLess<ElemT >>
	static void BubbleSort(ArrT &arr, const cs_size_t start, const cs_size_t len);

	/// 插入排序
	template<typename ArrT, 
		typename ElemT,
		typename CompareT = CsLess<ElemT >>
	static void InsertSort(ArrT &arr, const cs_size_t start, const cs_size_t len, const cs_bool bRecur = false);

	/// 希尔排序
	template<typename ArrT, typename ElemT>
	static void ShellSort(ArrT &arr, const cs_size_t start, const cs_size_t len);

	/// 选择排序
	template<typename ArrT, typename ElemT>
	static void SelectSort(ArrT &arr, const cs_size_t start, const cs_size_t len);

	/// 堆排序（算法有误）
	template<typename ArrT, typename ElemT>
	static void HeapSort(ArrT &arr, const cs_size_t start, const cs_size_t len);

	/// 归并排序（算法有误）
	template<typename ArrT, typename ElemT>
	static void MergeSort(ArrT &arr, const cs_size_t len);

	/// 快速排序
	template<typename ArrT, typename ElemT>
	static void QuickSort(ArrT &arr, const cs_size_t len);
};

/// 排序算法私有实现类
class CsSort_Private
{
	friend class CsSort;

private:
	/// 插入排序，递归实现（Recursive）
	template<typename ArrT, 
		typename ElemT,
		typename CompareT>
	static void InsertSorting(ArrT &arr, const cs_size_t start, const cs_size_t len, const CompareT &compareF);

	static cs_size_t LeftChild(const cs_size_t i);

	template<typename ElemT>
	static void Swap(ElemT* l, ElemT* r);

	/// 构建大根堆
	template<typename ArrT, typename ElemT>
	static void PercDown(ArrT &arr, const cs_size_t start, const cs_size_t len);

	/// 归并
	template<typename ArrT, typename ElemT>
	static void Merge(ArrT &arr, const cs_size_t first, const cs_size_t mid, const cs_size_t last);

	template<typename ArrT, typename ElemT>
	static void MergeSorting(ArrT &arr, const cs_size_t first, const cs_size_t last);

	template<typename ArrT, typename ElemT>
	static ElemT Median3(ArrT &arr, const cs_size_t left, const cs_size_t right);

	template<typename ArrT, typename ElemT>
	static void QuickSorting(ArrT &arr, const cs_size_t first, const cs_size_t last);
};

template<typename ArrT, typename ElemT, typename CompareT>
void CsSort::BubbleSort(ArrT &arr, const cs_size_t start, const cs_size_t len)
{
	CompareT compareF;
	for (cs_size_t i = 0; i < len; ++i)
	{
		for (cs_size_t j = 0; j < len - i - 1; ++j)
		{
			//if (arr[j + start + 1] < arr[j + start])
			if (compareF(arr[j + start + 1], arr[j + start]))
			{
				ElemT tmp(arr[j + start]);
				arr[j + start] = arr[j + start + 1];
				arr[j + start + 1] = tmp;
			}
		}
	}
}

template<typename ArrT, typename ElemT, typename CompareT>
void CsSort::InsertSort(ArrT &arr, const cs_size_t start, const cs_size_t len, const cs_bool bRecur)
{
	CompareT compareF;
	if (bRecur)
	{
		// 递归实现
		CsSort_Private::InsertSorting<ArrT, ElemT, CompareT>(arr, start, len, compareF);
		return;
	}

	// 非递归实现
	cs_size_t i, j;
	for (i = 1; i < len; ++i)
	{
		ElemT tmp(arr[i + start]);
		for (j = i; j > 0; --j)
		{
			if (compareF(tmp,arr[j + start - 1]))
			{
				arr[j + start] = arr[j + start - 1];
			}
			else
			{
				break;
			}
		}
		arr[j + start] = tmp;
	}
}

template<typename ArrT, typename ElemT>
void CsSort::ShellSort(ArrT &arr, const cs_size_t start, const cs_size_t len)
{
	cs_size_t i, j;
	for (cs_size_t inc = len / 2; inc > 0; inc /= 2)
	{
		for (i = inc; i < len; ++i)
		{
			ElemT tmp(arr[i + start]);
			for (j = i; j >= inc; j -= inc)
			{
				if (tmp < arr[j + start - inc])
				{
					arr[j + start] = arr[j + start - inc];
				}
				else
				{
					break;
				}
			}
			arr[j + start] = tmp;
		}
	}
}

template<typename ArrT, typename ElemT>
void CsSort::SelectSort(ArrT &arr, const cs_size_t start, const cs_size_t len)
{
	cs_size_t index;
	for (cs_size_t i = 0; i < len - 1; ++i)
	{
		ElemT tmp(arr[i + start]);
		index = i;
		for (cs_size_t j = i + 1; j < len; ++j)
		{
			if (arr[j + start] < tmp)
			{
				index = j;
				tmp = arr[j + start];
			}
		}
		if (index != i)
		{
			arr[index + start] = arr[i + start];
			arr[i + start] = tmp;
		}
	}
}

template<typename ArrT, typename ElemT>
void CsSort::HeapSort(ArrT &arr, const cs_size_t start, const cs_size_t len)
{
	for (cs_int i = len / 2; i >= 0; --i)
	{
		CsSort_Private::PercDown<ArrT, ElemT>(arr, i + start, len);
	}

	for (cs_size_t i = len - 1; i > 0; --i)
	{
		CsSort_Private::Swap<ElemT>(&arr[start], &arr[i + start]);
		CsSort_Private::PercDown<ArrT, ElemT>(arr, start, i);
	}
}

template<typename ArrT, typename ElemT>
void CsSort::MergeSort(ArrT &arr, const cs_size_t len)
{
	CsSort_Private::MergeSorting<ArrT, ElemT>(arr, 0, len - 1);
}

template<typename ArrT, typename ElemT>
void CsSort::QuickSort(ArrT &arr, const cs_size_t len)
{
	CsSort_Private::QuickSorting<ArrT, ElemT>(arr, 0, len - 1);
}

template<typename ArrT, typename ElemT, typename CompareT>
void CsSort_Private::InsertSorting(ArrT &arr, const cs_size_t start, const cs_size_t len, const CompareT &compareF)
{
	if (len > 1)
	{
		InsertSorting<ArrT, ElemT>(arr, start, len - 1, compareF);
		ElemT tmp(arr[len + start - 1]);
		cs_size_t i;
		for (i = len - 1; i > 0; i--)
		{
			if (compareF(tmp,arr[i + start - 1]))
			{
				arr[i + start] = arr[i + start - 1];
			}
			else
			{
				break;
			}
		}
		arr[i + start] = tmp;
	}
}

template<typename ElemT>
void CsSort_Private::Swap(ElemT* l, ElemT* r)
{
	ElemT tmp(*l);
	*l = *r;
	*r = tmp;
}

template<typename ArrT, typename ElemT>
void CsSort_Private::PercDown(ArrT &arr, const cs_size_t start, const cs_size_t len)
{
	ElemT tmp(arr[start]);
	cs_size_t j, nc;
	for (j = start; LeftChild(j) < len; j = nc)
	{
		nc = LeftChild(j);
		if (nc < len - 1 && arr[nc + 1] > arr[nc])
		{
			nc++;
		}
		if (tmp < arr[nc])
		{
			arr[j] = arr[nc];
		}
		else
		{
			break;
		}
	}
	arr[j] = tmp;
}

template<typename ArrT, typename ElemT>
void CsSort_Private::Merge(ArrT &arr, const cs_size_t first, const cs_size_t mid, const cs_size_t last)
{
	//设置indexA，并扫描subArray1 [first,mid)  
	//设置indexB,并扫描subArray2 [mid,last]  
	cs_size_t inda = first;
	cs_size_t indb = mid;
	cs_size_t noe = last - first + 1;//number of elements  

	ElemT *tmparr = (ElemT*)malloc(noe * sizeof(ElemT));
	cs_size_t indtmp = 0;

	//main loop  
	while (inda < mid && indb <= last)
	{
		if (arr[inda] <= arr[indb])
		{
			tmparr[indtmp++] = arr[inda++];
		}
		else
		{
			tmparr[indtmp++] = arr[indb++];
		}
	}

	//if some elements of the first subarray left.  
	while (inda < mid)
	{
		tmparr[indtmp++] = arr[inda++];
	}

	//if some elements of the second subarray left.  
	while (indb <= last)
	{
		tmparr[indtmp++] = arr[indb++];
	}

	//copy the sorted array back to the input memeory.  
	inda = first;
	indtmp = 0;
	for (cs_size_t i = 0; i < noe; ++i)
	{
		arr[inda++] = tmparr[indtmp++];
	}

	//free temporary memeory.  
	free(tmparr);
}

template<typename ArrT, typename ElemT>
void CsSort_Private::MergeSorting(ArrT &arr, const cs_size_t first, const cs_size_t last)
{
	if (first < last - 1)
	{
		cs_size_t mid = (first + last) / 2;
		MergeSorting<ArrT, ElemT>(arr, first, mid - 1);
		MergeSorting<ArrT, ElemT>(arr, mid, last);
		Merge<ArrT, ElemT>(arr, first, mid, last);
	}
}

template<typename ArrT, typename ElemT>
ElemT CsSort_Private::Median3(ArrT &arr, const cs_size_t left, const cs_size_t right)
{
	cs_size_t mid = (left + right) / 2;
	if (arr[left] > arr[mid])
	{
		Swap<ElemT>(&arr[left], &arr[right]);
	}
	if (arr[left] > arr[right])
	{
		Swap<ElemT>(&arr[left], &arr[right]);
	}
	if (arr[mid] > arr[right])
	{
		Swap<ElemT>(&arr[mid], &arr[right]);
	}
	Swap<ElemT>(&arr[mid], &arr[right - 1]);
	return arr[right - 1];
}

template<typename ArrT, typename ElemT>
void CsSort_Private::QuickSorting(ArrT &arr, const cs_size_t first, const cs_size_t last)
{
	const cs_size_t cutoff = 3;
	if (first + cutoff < last)
	{
		ElemT pivot(Median3<ArrT, ElemT>(arr, first, last));
		cs_size_t i = first, j = last - 1;//i,j初始化为比它们的正确值超出1.  
		for (;;)
		{
			while (arr[++i]<pivot){}
			while (arr[--j]>pivot){}
			if (i < j)
			{
				Swap<ElemT>(&arr[i], &arr[j]);
			}
			else
			{
				break;
			}
		}
		//restore pivot  
		Swap<ElemT>(&arr[i], &arr[last - 1]);
		QuickSorting<ArrT, ElemT>(arr, first, i - 1);
		QuickSorting<ArrT, ElemT>(arr, i + 1, last);
	}
	else
	{
		InsertSort<ArrT, ElemT>(arr, first, last - first + 1);
	}
}

#endif // _CSCORE_SORT_H_
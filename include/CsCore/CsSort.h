#ifndef _CSCORE_SORT_H_
#define _CSCORE_SORT_H_

#include "CsCoreGlobal.h"
#include "CsArray.h"

/// ArrType需下标操作元素的方法
/// ElemType需实现拷贝构造和等号重载的方法
/// arr：待排序的数组
/// start：待排序的数组起始位置
/// length：待排序的数组长度，注意是从start位开始的数组长度
class CsCore_Export CsSort
{
public:
	/// 冒泡排序
	template<typename ArrType, typename ElemType>
	static void BubbleSort(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 插入排序
	template<typename ArrType, typename ElemType>
	static void InsertSort(ArrType &arr, const cs_size_t start, const cs_size_t length);
	
	/// 插入排序，递归实现
	template<typename ArrType, typename ElemType>
	static void InsertSort_Recursive(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 希尔排序
	template<typename ArrType, typename ElemType>
	static void ShellSort(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 选择排序
	template<typename ArrType, typename ElemType>
	static void SelectSort(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 堆排序（算法有误）
	template<typename ArrType, typename ElemType>
	static void HeapSort(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 归并排序（算法有误）
	template<typename ArrType, typename ElemType>
	static void MergeSort(ArrType &arr, const cs_size_t length);

	/// 快速排序
	template<typename ArrType, typename ElemType>
	static void QuickSort(ArrType &arr, const cs_size_t length);

private:
	static cs_size_t LeftChild(const cs_size_t i);

	template<typename ElemType>
	static void Swap(ElemType* l, ElemType* r);

	/// 构建大根堆
	template<typename ArrType, typename ElemType>
	static void PercDown(ArrType &arr, const cs_size_t start, const cs_size_t length);

	/// 归并
	template<typename ArrType, typename ElemType>
	static void Merge(ArrType &arr, const cs_size_t first, const cs_size_t mid, const cs_size_t last);

	template<typename ArrType, typename ElemType>
	static void MergeSorting(ArrType &arr, const cs_size_t first, const cs_size_t last);

	template<typename ArrType, typename ElemType>
	static ElemType Median3(ArrType &arr, const cs_size_t left, const cs_size_t right);

	template<typename ArrType, typename ElemType>
	static void QuickSorting(ArrType &arr, const cs_size_t first, const cs_size_t last);

	CsSort();
	~CsSort();
};

CsSort::CsSort()
{

}

CsSort::~CsSort()
{

}

template<typename ArrType, typename ElemType>
void CsSort::BubbleSort(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	for (cs_size_t i = 0; i < length; ++i)
	{
		for (cs_size_t j = 0; j < length - i - 1; ++j)
		{
			if (arr[j + start] > arr[j + 1 + start])
			{
				ElemType tmp(arr[j + start]);
				arr[j + start] = arr[j + 1 + start];
				arr[j + 1 + start] = tmp;
			}
		}
	}
}

template<typename ArrType, typename ElemType>
void CsSort::InsertSort(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	cs_size_t i, j;
	for (i = 1; i < length; ++i)
	{
		ElemType tmp(arr[i + start]);
		for (j = i; j > 0; --j)
		{
			if (arr[j - 1 + start] > tmp)
			{
				arr[j + start] = arr[j - 1 + start];
			}
			else
			{
				break;
			}
		}
		arr[j + start] = tmp;
	}
}

template<typename ArrType, typename ElemType>
void CsSort::InsertSort_Recursive(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	if (length > 1)
	{
		InsertSort_Recursive<ArrType, ElemType>(arr, start, length - 1);
		ElemType key(arr[length - 1 + start]);
		cs_size_t i;
		for (i = length - 1; i > 0; i--)
		{
			if (arr[i - 1 + start] > key)
			{
				arr[i + start] = arr[i - 1 + start];
			}
			else
			{
				break;
			}
		}
		arr[i + start] = key;
	}
}

template<typename ArrType, typename ElemType>
void CsSort::ShellSort(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	cs_size_t i, j;
	for (cs_size_t inc = length / 2; inc > 0; inc /= 2)
	{
		for (i = inc; i < length; ++i)
		{
			ElemType tmp(arr[i + start]);
			for (j = i; j >= inc; j -= inc)
			{
				if (arr[j - inc + start] > tmp)
				{
					arr[j + start] = arr[j - inc + start];
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

template<typename ArrType, typename ElemType>
void CsSort::SelectSort(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	cs_size_t index;
	for (cs_size_t i = 0; i < length - 1; ++i)
	{
		ElemType minv(arr[i + start]);
		index = i;
		for (cs_size_t j = i + 1; j < length; ++j)
		{
			if (arr[j + start] < minv)
			{
				index = j;
				minv = arr[j + start];
			}
		}
		if (index != i)
		{
			arr[index + start] = arr[i + start];
			arr[i + start] = minv;
		}
	}
}

cs_size_t CsSort::LeftChild(const cs_size_t i)
{
	return 2 * i + 1;
}

template<typename ElemType>
void CsSort::Swap(ElemType* l, ElemType* r)
{
	ElemType tmp(*l);
	*l = *r;
	*r = tmp;
}

template<typename ArrType, typename ElemType>
void CsSort::PercDown(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	ElemType tmp(arr[start]);
	cs_size_t j, nc;
	for (j = start; LeftChild(j) < length; j = nc)
	{
		nc = LeftChild(j);
		if (nc < length - 1 && arr[nc + 1] > arr[nc])
		{
			nc++;
		}
		if (arr[nc] > tmp)
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

template<typename ArrType, typename ElemType>
void CsSort::HeapSort(ArrType &arr, const cs_size_t start, const cs_size_t length)
{
	for (cs_int i = length / 2; i >= 0; --i)
	{
		PercDown<ArrType, ElemType>(arr, i + start, length);
	}

	for (cs_size_t i = length - 1; i > 0; --i)
	{
		Swap<ElemType>(&arr[start], &arr[i + start]);
		PercDown<ArrType, ElemType>(arr, start, i);
	}
}

template<typename ArrType, typename ElemType>
void CsSort::Merge(ArrType &arr, const cs_size_t first, const cs_size_t mid, const cs_size_t last)
{
	//设置indexA，并扫描subArray1 [first,mid)  
	//设置indexB,并扫描subArray2 [mid,last]  
	cs_size_t inda = first;
	cs_size_t indb = mid;
	cs_size_t noe = last - first + 1;//number of elements  

	ElemType *tmparr = (ElemType*)malloc(noe * sizeof(ElemType));
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

template<typename ArrType, typename ElemType>
void CsSort::MergeSorting(ArrType &arr, const cs_size_t first, const cs_size_t last)
{
	if (first < last - 1)
	{
		cs_size_t mid = (first + last) / 2;
		MergeSorting<ArrType, ElemType>(arr, first, mid - 1);
		MergeSorting<ArrType, ElemType>(arr, mid, last);
		Merge<ArrType, ElemType>(arr, first, mid, last);
	}
}

template<typename ArrType, typename ElemType>
void CsSort::MergeSort(ArrType &arr, const cs_size_t length)
{
	MergeSorting<ArrType, ElemType>(arr, 0, length - 1);
}

template<typename ArrType, typename ElemType>
ElemType CsSort::Median3(ArrType &arr, const cs_size_t left, const cs_size_t right)
{
	cs_size_t mid = (left + right) / 2;
	if (arr[left] > arr[mid])
	{
		Swap<ElemType>(&arr[left], &arr[right]);
	}
	if (arr[left] > arr[right])
	{
		Swap<ElemType>(&arr[left], &arr[right]);
	}
	if (arr[mid] > arr[right])
	{
		Swap<ElemType>(&arr[mid], &arr[right]);
	}
	Swap<ElemType>(&arr[mid], &arr[right - 1]);
	return arr[right - 1];
}

template<typename ArrType, typename ElemType>
void CsSort::QuickSorting(ArrType &arr, const cs_size_t first, const cs_size_t last)
{
	const cs_size_t cutoff = 3;
	if (first + cutoff < last)
	{
		ElemType pivot(Median3<ArrType, ElemType>(arr, first, last));
		cs_size_t i = first, j = last - 1;//i,j初始化为比它们的正确值超出1.  
		for (;;)
		{
			while (arr[++i]<pivot){}
			while (arr[--j]>pivot){}
			if (i < j)
			{
				Swap<ElemType>(&arr[i], &arr[j]);
			}
			else
			{
				break;
			}
		}
		//restore pivot  
		Swap<ElemType>(&arr[i], &arr[last - 1]);
		QuickSorting<ArrType, ElemType>(arr, first, i - 1);
		QuickSorting<ArrType, ElemType>(arr, i + 1, last);
	}
	else
	{
		InsertSort<ArrType, ElemType>(arr, first, last - first + 1);
	}
}

template<typename ArrType, typename ElemType>
void CsSort::QuickSort(ArrType &arr, const cs_size_t length)
{
	QuickSorting<ArrType, ElemType>(arr, 0, length - 1);
}

#endif // _CSCORE_SORT_H_
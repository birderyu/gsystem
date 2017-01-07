#ifndef _CORE_SORT_INLINE_H_
#define _CORE_SORT_INLINE_H_

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::BubbleSort(ArrT &arr, gsize start, gsize len)
{
	CompareT compareF;
	for (gsize i = 0; i < len; ++i)
	{
		for (gsize j = 0; j < len - i - 1; ++j)
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
inline void GSort::InsertSort(ArrT &arr, gsize start, gsize len, gbool bRecur)
{
	CompareT compareF;
	if (bRecur)
	{
		// 递归实现
		GSort_Ex::InsertSorting<ArrT, ElemT, CompareT>(arr, start, len, compareF);
		return;
	}

	// 非递归实现
	gsize i, j;
	for (i = 1; i < len; ++i)
	{
		ElemT tmp(arr[i + start]);
		for (j = i; j > 0; --j)
		{
			if (compareF(tmp, arr[j + start - 1]))
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

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::ShellSort(ArrT &arr, gsize start, gsize len)
{
	CompareT compareF;
	gsize i, j;
	for (gsize inc = len / 2; inc > 0; inc /= 2)
	{
		for (i = inc; i < len; ++i)
		{
			ElemT tmp(arr[i + start]);
			for (j = i; j >= inc; j -= inc)
			{
				if (compareF(tmp, arr[j + start - inc]))
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

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::SelectSort(ArrT &arr, gsize start, gsize len)
{
	CompareT compareF;
	gsize index;
	for (gsize i = 0; i < len - 1; ++i)
	{
		ElemT tmp(arr[i + start]);
		index = i;
		for (gsize j = i + 1; j < len; ++j)
		{
			if (compareF(arr[j + start], tmp))
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

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::HeapSort(ArrT &arr, gsize start, gsize len)
{
	CompareT compareF;
	for (gint i = len / 2; i >= 0; --i)
	{
		GSort_Ex::PercDown<ArrT, ElemT, CompareT>(arr, start, i, len, compareF);
	}

	for (gint i = len - 1; i > 0; --i)
	{
		GSort_Ex::Swap<ElemT>(&arr[start], &arr[i + start]);
		GSort_Ex::PercDown<ArrT, ElemT, CompareT>(arr, start, 0, i, compareF);
	}
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::MergeSort(ArrT &arr, gsize start, gsize len)
{
	if (len <= 0)
	{
		return;
	}
	CompareT compareF;
	GSort_Ex::MergeSorting<ArrT, ElemT, CompareT>(arr, 0, len - 1, compareF);
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort::QuickSort(ArrT &arr, gsize start, gsize len)
{
	CompareT compareF;
	GSort_Ex::QuickSorting<ArrT, ElemT, CompareT>(arr, start, start + len - 1, compareF);
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort_Ex::InsertSorting(ArrT &arr, const gsize start, const gsize len, const CompareT &compareF)
{
	if (len > 1)
	{
		InsertSorting<ArrT, ElemT>(arr, start, len - 1, compareF);
		ElemT tmp(arr[len + start - 1]);
		gsize i;
		for (i = len - 1; i > 0; i--)
		{
			if (compareF(tmp, arr[i + start - 1]))
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
inline void GSort_Ex::Swap(ElemT* l, ElemT* r)
{
	ElemT tmp(*l);
	*l = *r;
	*r = tmp;
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort_Ex::PercDown(ArrT &arr, gsize start, gsize i, gsize len, const CompareT &compareF)
{
	ElemT tmp(arr[start + i]);
	gsize j, nc;
	for (j = i; (nc = LeftChild(j)) < len; j = nc)
	{
		if (nc < len - 1 && compareF(arr[start + nc], arr[start + nc + 1]))
		{
			nc++;
		}
		if (compareF(tmp, arr[start + nc]))
		{
			arr[start + j] = arr[start + nc];
		}
		else
		{
			break;
		}
	}
	arr[start + j] = tmp;
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort_Ex::Merge(ArrT &arr, gsize first, gsize mid, gsize last, const CompareT &compareF)
{
	//设置indexA，并扫描subArray1 [first,mid)  
	//设置indexB,并扫描subArray2 [mid,last]  
	gsize id_a = first, id_b = mid,
		len = last - first + 1;
	if (len <= 0)
	{
		return;
	}

	ElemT *arr_tmp = (ElemT*)GMalloc(len * sizeof(ElemT));
	gsize id_tmp = 0;

	//main loop  
	while (id_a < mid && id_b <= last)
	{
		if (!compareF(arr[id_b], arr[id_a]))
		{
			// arr[id_a] <= arr[id_b]
			arr_tmp[id_tmp++] = arr[id_a++];
		}
		else
		{
			// arr[id_a] > arr[id_b]
			arr_tmp[id_tmp++] = arr[id_b++];
		}
	}

	//if some elements of the first subarray left.  
	while (id_a < mid)
	{
		arr_tmp[id_tmp++] = arr[id_a++];
	}

	//if some elements of the second subarray left.  
	while (id_b <= last)
	{
		arr_tmp[id_tmp++] = arr[id_b++];
	}

	//copy the sorted array back to the input memeory.  
	for (gsize i = 0; i < len; ++i)
	{
		arr[first + 1] = arr_tmp[i];
	}

	//free temporary memeory.  
	GFree(arr_tmp);
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort_Ex::MergeSorting(ArrT &arr, gsize first, gsize last, const CompareT &compareF)
{
	if (first < last - 1)
	{
		gsize mid = (first + last) / 2;
		MergeSorting<ArrT, ElemT, CompareT>(arr, first, mid - 1, compareF);
		MergeSorting<ArrT, ElemT, CompareT>(arr, mid, last, compareF);
		Merge<ArrT, ElemT, CompareT>(arr, first, mid, last, compareF);
	}
}

template<typename ArrT, typename ElemT, typename CompareT>
inline ElemT GSort_Ex::Median3(ArrT &arr, gsize left, gsize right, const CompareT &compareF)
{
	gsize mid = (left + right) / 2;
	if (compareF(arr[mid], arr[left]))
	{
		Swap<ElemT>(&arr[left], &arr[right]);
	}
	if (compareF(arr[right], arr[left]))
	{
		Swap<ElemT>(&arr[left], &arr[right]);
	}
	if (compareF(arr[right], arr[mid]))
	{
		Swap<ElemT>(&arr[mid], &arr[right]);
	}
	Swap<ElemT>(&arr[mid], &arr[right - 1]);
	return arr[right - 1];
}

template<typename ArrT, typename ElemT, typename CompareT>
inline void GSort_Ex::QuickSorting(ArrT &arr, gsize first, gsize last, const CompareT &compareF)
{
	const gsize cutoff = 3;
	if (first + cutoff < last)
	{
		ElemT pivot(Median3<ArrT, ElemT, CompareT>(arr, first, last, compareF));
		gsize i = first, j = last - 1;//i,j初始化为比它们的正确值超出1.  
		for (;;)
		{
			while (compareF(arr[++i], pivot)){}
			while (compareF(arr[--j], pivot)){}
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
		QuickSorting<ArrT, ElemT, CompareT>(arr, first, i - 1, compareF);
		QuickSorting<ArrT, ElemT, CompareT>(arr, i + 1, last, compareF);
	}
	else
	{
		GSort::InsertSort<ArrT, ElemT, CompareT>(arr, first, last - first + 1);
	}
}

#endif // _CORE_SORT_INLINE_H_
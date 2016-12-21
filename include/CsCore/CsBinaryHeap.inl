#ifndef _CORE_BINARY_HEAP_INLINE_
#define _CORE_BINARY_HEAP_INLINE_

template<typename DataT, typename CompareT>
CsBinaryHeap<DataT, CompareT>::CsBinaryHeap(cs_size_t capacity, cs_size_t add_size)
:m_nSize(0), m_tHeap(capacity), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = CS_HEAP_DEFAULT_ADD_SIZE;
	}
}

template<typename DataT, typename CompareT>
CsBinaryHeap<DataT, CompareT>::CsBinaryHeap(const CsArray<DataT> &arr, cs_size_t add_size)
:m_nSize(arr.Size()), m_tHeap(arr.Size()), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = CS_HEAP_DEFAULT_ADD_SIZE;
	}
	Append(arr);
}

template<typename DataT, typename CompareT>
CsBinaryHeap<DataT, CompareT>::CsBinaryHeap(DataT *arr, cs_size_t size, cs_size_t add_size)
:m_nSize(size), m_tHeap(size), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = CS_HEAP_DEFAULT_ADD_SIZE;
	}
	Append(arr, size);
}

template<typename DataT, typename CompareT>
CsBinaryHeap<DataT, CompareT>::CsBinaryHeap(const CsBinaryHeap<DataT, CompareT> &heap)
:m_nSize(heap.Size()), m_tHeap(heap.m_tHeap), m_nAddSize(CS_HEAP_DEFAULT_ADD_SIZE)
{

}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(const CsArray<DataT> &arr)
{
	Append(arr, 0, arr.Size());
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(const CsArray<DataT> &arr, cs_size_t start, cs_size_t size)
{
	AppendT<CsArray<DataT>>(arr, start, size);
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(DataT *arr, cs_size_t arr_size)
{
	Append(arr, 0, arr_size);
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(DataT *arr, cs_size_t start, cs_size_t size)
{
	AppendT<DataT*>(arr, start, size);
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(const CsBinaryHeap<DataT, CompareT> &heap)
{
	Append(heap.m_tHeap);
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Append(const CsBinaryHeap<DataT, CompareT> &heap, cs_size_t start, cs_size_t size)
{
	Append(heap.m_tHeap, start, size);
}

template<typename DataT, typename CompareT>
template<typename ArrT>
cs_void CsBinaryHeap<DataT, CompareT>::AppendT(const ArrT &arr)
{
	AppendT<ArrT>(arr, 0, arr.Size());
}

template<typename DataT, typename CompareT>
template<typename ArrT>
cs_void CsBinaryHeap<DataT, CompareT>::AppendT(const ArrT &arr, cs_size_t start, cs_size_t size)
{
	if (size <= 0 ||
		!Reserve(m_nSize + size))
	{
		return;
	}
	if (m_nSize <= 0)
	{
		// 初始化
		for (cs_size_t i = 0; i < size; i++)
		{
			m_tHeap[i] = arr[i + start];
		}
		m_nSize += size;
		for (cs_size_t i = m_nSize / 2; i >= 1; i--)
		{
			DataT y = m_tHeap[i]; // 子树的根  

			// 寻找放置y的位置  
			cs_size_t c = 2 * i; // c 的父节点是y的目标位置  

			while (c <= m_nSize)
			{
				// 使heap[c]是较小的子节点  
				if (c < m_nSize &&
					m_fCompare(m_tHeap[c + 1], m_tHeap[c]))
				{
					c++;
				}

				// 能把y放入heap[c/2]吗? 
				if (!m_fCompare(m_tHeap[c], y)) break;  // 能  

				// 不能  
				m_tHeap[c / 2] = m_tHeap[c]; // 子节点上移  
				c *= 2;              // 下移一层  
			}

			m_tHeap[c / 2] = y;
		}
	}
	else
	{
		for (cs_size_t i = 0; i < size; i++)
		{
			Insert(arr[i + start]);
		}
	}
}

template<typename DataT, typename CompareT>
cs_size_t CsBinaryHeap<DataT, CompareT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename CompareT>
cs_bool CsBinaryHeap<DataT, CompareT>::Reserve(cs_size_t size)
{
	cs_size_t capacity = m_tHeap.Size();
	if (size <= capacity)
	{
		return true;
	}
	if (size - capacity < m_nAddSize)
	{
		// 按照扩容步长进行扩容
		size = capacity + m_nAddSize;
	}
	return m_tHeap.Resize(size);
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Insert(const DataT &data)
{
	cs_size_t capacity = m_tHeap.Size();
	if (capacity <= m_nSize)
	{
		if (!Reserve(m_nSize + 1))
		{
			return;
		}
	}

	cs_size_t pos = ++m_nSize;
	while (pos != 1 &&
		m_fCompare(data, m_tHeap[pos / 2]))
	{
		m_tHeap[pos] = m_tHeap[pos / 2];	// 将元素下移  
		pos /= 2;							// 移向父节点  
	}
	m_tHeap[pos] = data;
}

template<typename DataT, typename CompareT>
cs_bool CsBinaryHeap<DataT, CompareT>::Pop(DataT *data)
{
	if (m_nSize == 0)
	{
		return false;
	}

	if (data)
	{
		*data = m_tHeap[1];
	}

	DataT y = m_tHeap[m_nSize--]; //最后一个元素  

	// 从根开始, 为y寻找合适的位置  
	cs_int i = 1,  // 堆的当前节点  
		ci = 2;  // i的子节点  

	while (ci <= m_nSize)
	{
		// 使heap[ci] 是i较小的子节点  
		if (ci < m_nSize
			&& m_fCompare(m_tHeap[ci + 1], m_tHeap[ci]))
			ci++;

		// 能把y放入heap[i]吗?  
		if (!m_fCompare(m_tHeap[ci], y)) break;  // 能  

		// 不能  
		m_tHeap[i] = m_tHeap[ci]; // 子节点上移  
		i = ci;             // 下移一层  
		ci *= 2;
	}

	m_tHeap[i] = y;

	return true;
}

template<typename DataT, typename CompareT>
cs_bool CsBinaryHeap<DataT, CompareT>::Top(DataT &data) const
{
	if (m_nSize <= 0)
	{
		return false;
	}
	data = m_tHeap[1];
	return true;
}

template<typename DataT, typename CompareT>
cs_void CsBinaryHeap<DataT, CompareT>::Output() const
{
	cout << "The " << m_nSize
		<< " elements are" << endl;
	for (cs_size_t i = 1; i <= m_nSize; i++)
		cout << m_tHeap[i] << ' ';
	cout << endl;
}

#endif // _CORE_BINARY_HEAP_INLINE_
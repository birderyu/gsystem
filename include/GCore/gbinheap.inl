#ifndef _CORE_BINARY_HEAP_INLINE_
#define _CORE_BINARY_HEAP_INLINE_

namespace gsystem { // gsystem

template<typename DataT, typename CompareT>
CompareT GBinHeap<DataT, CompareT>::m_fCompare;

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT>::GBinHeap(gsize capacity, gsize add_size)
 : m_nSize(0), m_tHeap(capacity + 1), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = G_BINARY_HEAP_DEFAULT_ADD_SIZE;
	}
}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT>::GBinHeap(const GArray<DataT> &arr, gsize add_size)
:m_nSize(arr.Size()), m_tHeap(arr.Size() + 1), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = G_BINARY_HEAP_DEFAULT_ADD_SIZE;
	}
	Append(arr);
}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT>::GBinHeap(DataT *arr, gsize size, gsize add_size)
:m_nSize(size), m_tHeap(size + 1), m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = G_BINARY_HEAP_DEFAULT_ADD_SIZE;
	}
	Append(arr, size);
}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT>::GBinHeap(const GBinHeap<DataT, CompareT> &heap)
:m_nSize(heap.m_nSize), m_tHeap(heap.m_tHeap), m_nAddSize(G_BINARY_HEAP_DEFAULT_ADD_SIZE)
{

}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT>::GBinHeap(GBinHeap<DataT, CompareT> &&heap)
:m_nSize(heap.m_nSize), m_tHeap(GMove(heap.m_tHeap)), m_nAddSize(G_BINARY_HEAP_DEFAULT_ADD_SIZE)
{
	heap.m_nSize = 0;
}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT> &GBinHeap<DataT, CompareT>::operator=(const GBinHeap<DataT, CompareT> &heap)
{
	if (this == &heap)
	{
		return *this;
	}
	m_nSize = heap.m_nSize;
	m_tHeap = heap.m_tHeap;
	return *this;
}

template<typename DataT, typename CompareT>
GINLINE GBinHeap<DataT, CompareT> &GBinHeap<DataT, CompareT>::operator=(GBinHeap<DataT, CompareT> &&heap)
{
	if (this == &heap)
	{
		return *this;
	}
	m_nSize = heap.m_nSize;
	m_tHeap = GMove(heap.m_tHeap);
	heap.m_nSize = 0;
	return *this;
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(const GArray<DataT> &arr)
{
	Append(arr, 0, arr.Size());
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(const GArray<DataT> &arr, gsize start, gsize size)
{
	AppendT<GArray<DataT>>(arr, start, size);
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(DataT *arr, gsize arr_size)
{
	Append(arr, 0, arr_size);
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(DataT *arr, gsize start, gsize size)
{
	AppendT<DataT*>(arr, start, size);
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(const GBinHeap<DataT, CompareT> &heap)
{
	Append(heap.m_tHeap);
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Append(const GBinHeap<DataT, CompareT> &heap, gsize start, gsize size)
{
	Append(heap.m_tHeap, start, size);
}

template<typename DataT, typename CompareT>
template<typename ArrT>
GINLINE gvoid GBinHeap<DataT, CompareT>::AppendT(const ArrT &arr)
{
	AppendT<ArrT>(arr, 0, arr.Size());
}

template<typename DataT, typename CompareT>
template<typename ArrT>
GINLINE gvoid GBinHeap<DataT, CompareT>::AppendT(const ArrT &arr, gsize start, gsize size)
{
	if (size <= 0)
	{
		return;
	}
	Reserve(m_nSize + size);
	if (m_nSize <= 0)
	{
		// 初始化
		for (gsize i = 0; i < size; i++)
		{
			m_tHeap[i + 1] = arr[i + start];
		}
		m_nSize += size;
		for (gsize i = m_nSize / 2; i >= 1; i--)
		{
			DataT &y = m_tHeap[i]; // 子树的根  

			// 寻找放置y的位置  
			gsize c = 2 * i; // c 的父节点是y的目标位置  

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
		for (gsize i = 0; i < size; i++)
		{
			Insert(arr[i + start]);
		}
	}
}

template<typename DataT, typename CompareT>
GINLINE gbool GBinHeap<DataT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template<typename DataT, typename CompareT>
GINLINE gsize GBinHeap<DataT, CompareT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename CompareT>
GINLINE gsize GBinHeap<DataT, CompareT>::Capacity() const
{
	return m_tHeap.Size() - 1;
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Reserve(gsize size)
{
	gsize capacity = Capacity();
	if (size <= capacity)
	{
		return;
	}
	if (size - capacity < m_nAddSize)
	{
		// 按照扩容步长进行扩容
		size = capacity + m_nAddSize;
	}
	m_tHeap.Resize(size + 1);
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Insert(const DataT &data)
{
	gsize capacity = Capacity();
	if (capacity <= m_nSize)
	{
		Reserve(m_nSize + 1);
	}

	gsize pos = ++m_nSize;
	while (pos != 1 &&
		m_fCompare(data, m_tHeap[pos / 2]))
	{
		m_tHeap[pos] = m_tHeap[pos / 2];	// 将元素下移  
		pos /= 2;							// 移向父节点  
	}
	m_tHeap[pos] = data;
}

template<typename DataT, typename CompareT>
GINLINE gbool GBinHeap<DataT, CompareT>::Pop(DataT *data)
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
	gint i = 1,  // 堆的当前节点  
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
GINLINE DataT GBinHeap<DataT, CompareT>::Top() const
{
	GASSERT(m_nSize > 0);
	return m_tHeap[1];
}

template<typename DataT, typename CompareT>
GINLINE gvoid GBinHeap<DataT, CompareT>::Output() const
{
	cout << "The " << m_nSize
		<< " elements are" << endl;
	for (gsize i = 1; i <= m_nSize; i++)
		cout << m_tHeap[i] << ' ';
	cout << endl;
}

}  // namespace gsystem

#endif // _CORE_BINARY_HEAP_INLINE_
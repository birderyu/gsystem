#ifndef _CORE_DYNAMIC_ARRAY_INLINE_
#define _CORE_DYNAMIC_ARRAY_INLINE_

#include "garrays.h"
#include "gserialize.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray()
: m_pData(GNULL), m_nSize(0)
{

}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<DataT>(m_nSize);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(gsize size, const DataT &data)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<DataT>(m_nSize, data);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(const GDynamicArray<DataT> &array)
: m_pData(GNULL), m_nSize(array.m_nSize)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<DataT>(array.m_pData, 0, array.m_nSize);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(GDynamicArray<DataT> &&arr)
: m_pData(arr.m_pData), m_nSize(arr.m_nSize)
{
	arr.m_pData = GNULL;
	arr.m_nSize = 0;
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(const GArray<DataT> &array, gsize start, gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (size <= 0 || start >= array.Size())
	{
		m_nSize = 0;
		return;
	}
	m_pData = GArrays::CreateArray<DataT>(&array[0], start, size);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::~GDynamicArray()
{
	Destroy();
}

template <typename DataT>
GINLINE gsize GDynamicArray<DataT>::Size() const
{
	return m_nSize;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::IsEmpty() const
{
	return m_pData == GNULL
		|| m_nSize <= 0;
}

template <typename DataT> GINLINE
gvoid GDynamicArray<DataT>::Resize(gsize size)
{
	if (m_nSize == size)
	{
		return;
	}

	if (size <= 0)
	{
		// 直接清空数组
		return Destroy();
	}

	// 当数组不存在时，会构建新的数组
	m_pData = GArrays::ResizeArray<DataT>(m_pData, m_nSize, size);
	m_nSize = size;
}

template <typename DataT> GINLINE 
gvoid GDynamicArray<DataT>::Resize(gsize size, const DataT &data)
{
	if (m_nSize == size)
	{
		return;
	}

	if (size <= 0)
	{
		// 直接清空数组
		return Destroy();
	}

	m_pData = GArrays::ResizeArray<DataT>(m_pData, m_nSize, size, data);
	m_nSize = size;
}

template <typename DataT> GINLINE
gvoid GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start)
{
	if (new_size == m_nSize && start == 0 && size == m_nSize)
	{
		return;
	}
	
	if (new_size <= 0)
	{
		// 直接清空数组
		return Destroy();
	}

	// 重新分配内存
	m_pData = GArrays::ResizeArray<DataT>(m_pData, start, size, new_size, new_start);
	m_nSize = new_size;
}

template <typename DataT> GINLINE
gvoid GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start, const DataT &data)
{
	if (new_size == m_nSize && start == 0 && size == m_nSize)
	{
		return;
	}

	if (new_size <= 0)
	{
		// 直接清空数组
		return Destroy();
	}

	if (!m_pData)
	{
		m_pData = GArrays::CreateArray<DataT>(new_start, data);
	}
	else
	{
		// 重新分配内存
		m_pData = GArrays::ResizeArray<DataT>(m_pData, start, size, new_size, new_start);
	}
	m_nSize = new_size;
}

template <typename DataT>
gvoid GDynamicArray<DataT>::Clear()
{
	GArrays::ClearArray<DataT>(m_pData, m_nSize);
}

template <typename DataT>
GINLINE gvoid GDynamicArray<DataT>::Destroy()
{
	GArrays::DestoryArray<DataT>(m_pData, m_nSize);
	m_pData = GNULL;
	m_nSize = 0;
}

template <typename DataT>
GINLINE DataT &GDynamicArray<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE const DataT &GDynamicArray<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE DataT *GDynamicArray<DataT>::CursorAt(gsize pos)
{
	return m_pData + pos;
}

template <typename DataT>
GINLINE const DataT *GDynamicArray<DataT>::CursorAt(gsize pos) const
{
	return m_pData + pos;
}

template <typename DataT>
GINLINE DataT &GDynamicArray<DataT>::operator[](gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE const DataT &GDynamicArray<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE gvoid GDynamicArray<DataT>::RemoveAt(gsize pos)
{
	GASSERT(m_nSize > 0 && pos < m_nSize);
	if (1 == m_nSize)
	{
		// 直接销毁数组
		Destroy();
	}
	else
	{
		m_pData = GArrays::RemoveArrayElementAt<DataT>(m_pData, m_nSize, pos);
		m_nSize--;
	}
}

template <typename DataT>
GINLINE GDynamicArray<DataT> &GDynamicArray<DataT>::operator=(const GDynamicArray<DataT> &arr)
{
	if (this == &arr)
	{
		return *this;
	}
	if (arr.IsEmpty())
	{
		Destroy();
		return *this;
	}
	if (m_pData)
	{
		m_pData = GArrays::CopyArrayFrom<DataT>(m_pData, m_nSize, arr.m_pData, arr.m_nSize);
	}
	else
	{
		m_pData = GArrays::CreateArray<DataT>(arr.m_pData, 0, arr.m_nSize);
	}
	m_nSize = arr.m_nSize;
	return *this;
}

template <typename DataT>
GINLINE GDynamicArray<DataT> &GDynamicArray<DataT>::operator=(GDynamicArray<DataT> &&arr)
{
	if (this == &arr)
	{
		return *this;
	}
	Destroy();
	m_pData = arr.m_pData;
	m_nSize = arr.m_nSize;
	arr.m_pData = GNULL;
	arr.m_nSize = 0;
	return *this;
}

template <typename DataT>
gbool GDynamicArray<DataT>::operator==(const GDynamicArray<DataT> &arr)
{
	if (this == &arr)
	{
		return true;
	}
	gsize size = Size();
	if (size != arr.Size())
	{
		return false;
	}
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) != arr.GetAt(i))
		{
			return false;
		}
	}
	return true;
}

template <typename DataT>
GINLINE guint GDynamicArray<DataT>::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::DynamicArray);
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Serialize(GArchive &archive) const
{
	if (!archive.Input())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	gsize size = Size();
	archive << size;

	for (gsize i = 0; i < size; i++)
	{
		if (!GSerialize<DataT>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Deserialize(GArchive &archive)
{
	if (!archive.Output())
	{
		return false;
	}
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	gsize size = 0;
	archive >> size;
	Destroy(); // 清空所有数据
	Resize(size);

	for (gsize i = 0; i < size; i++)
	{
		if (!GDeserialize<DataT>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

} // namespace gsystem

#endif // _CORE_DYNAMIC_ARRAY_INLINE_
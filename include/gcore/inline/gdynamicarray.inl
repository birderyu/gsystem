#ifndef _CORE_DYNAMIC_ARRAY_INLINE_
#define _CORE_DYNAMIC_ARRAY_INLINE_

#include "garrays.h"
#include "gserialize.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray()
: m_pData(GNULL), m_nSize(0)
{

}

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray(gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<T>(m_nSize);
}

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray(gsize size, const T &copyable)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<T>(m_nSize, copyable);
}

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray(const GDynamicArray<T> &array)
: m_pData(GNULL), m_nSize(array.m_nSize)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArrays::CreateArray<T>(array.m_pData, 0, array.m_nSize);
}

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray(GDynamicArray<T> &&arr)
: m_pData(arr.m_pData), m_nSize(arr.m_nSize)
{
	arr.m_pData = GNULL;
	arr.m_nSize = 0;
}

template <typename T>
GINLINE GDynamicArray<T>::GDynamicArray(const GArray<T> &array, gsize start, gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (size <= 0 || start >= array.Size())
	{
		m_nSize = 0;
		return;
	}
	m_pData = GArrays::CreateArray<T>(&array[0], start, size);
}

template <typename T>
GINLINE GDynamicArray<T>::~GDynamicArray()
{
	Destroy();
}

template <typename T>
GINLINE gsize GDynamicArray<T>::Size() const
{
	return m_nSize;
}

template <typename T>
GINLINE gbool GDynamicArray<T>::IsEmpty() const
{
	return m_pData == GNULL
		|| m_nSize <= 0;
}

template <typename T> GINLINE
gvoid GDynamicArray<T>::Resize(gsize size)
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
	m_pData = GArrays::ResizeArray<T>(m_pData, m_nSize, size);
	m_nSize = size;
}

template <typename T> GINLINE 
gvoid GDynamicArray<T>::Resize(gsize size, const T &copyable)
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

	m_pData = GArrays::ResizeArray<T>(m_pData, m_nSize, size, copyable);
	m_nSize = size;
}

template <typename T> GINLINE
gvoid GDynamicArray<T>::Resize(gsize new_size, gsize start, gsize size, gsize new_start)
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
	m_pData = GArrays::ResizeArray<T>(m_pData, start, size, new_size, new_start);
	m_nSize = new_size;
}

template <typename T> GINLINE
gvoid GDynamicArray<T>::Resize(gsize new_size, gsize start, gsize size, gsize new_start, const T &copyable)
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
		m_pData = GArrays::CreateArray<T>(new_start, copyable);
	}
	else
	{
		// 重新分配内存
		m_pData = GArrays::ResizeArray<T>(m_pData, start, size, new_size, new_start);
	}
	m_nSize = new_size;
}

template <typename T>
GINLINE gvoid GDynamicArray<T>::Clear()
{
	GArrays::ClearArray<T>(m_pData, m_nSize);
}

template <typename T> 
GINLINE
gsize GDynamicArray<T>::Remove(const T &value)
{
	if (IsEmpty())
	{
		return 0;
	}

	// 收集需要移除的元素下标
	gsize old_size = m_nSize;
	gsize *remove_indexs = GArrays::CreateArray<gsize>(old_size);
	gsize remove_size = 0;
	for (gsize i = 0; i < m_nSize; i++)
	{
		if (m_pData[i] == value)
		{
			remove_indexs[remove_size++] = i;
			remove_indexs[remove_size] = -1;
		}
	}

	// 移除元素
	if (old_size == remove_size)
	{
		Destroy();
	}
	else if (remove_size == 0)
	{
		// do nothing
	}
	else
	{
		// 分段拷贝元素
		T *data = GArrays::CreateArray<T>(old_size - remove_size);
		gsize size = 0;
		// [0 - remove_indexs[0])
		if (remove_indexs[0] > 0)
		{
			gsize copy_size = remove_indexs[0];
			GMemCopy(data, m_pData, sizeof(T) * remove_indexs[0]);
			size += copy_size;
		}
		for (gsize i = 0; i < remove_size; i++)
		{
			if (i != 0)
			{
				if (remove_indexs[i] - remove_indexs[i - 1] > 1)
				{
					//(remove_indexs[i - 1] - remove_indexs[i]]
					gsize copy_size = remove_indexs[i] - remove_indexs[i - 1] - 1;
					GMemCopy(data + size,
						m_pData + remove_indexs[i - 1] + 1,
						sizeof(T) * copy_size);
					size += copy_size;
				}
				
			}
			// 析构元素
			GDestruct<T>(m_pData + remove_indexs[i]);
		}
		if (old_size - 1 > remove_indexs[remove_size - 1])
		{
			// (remove_indexs[remove_size - 1] - (old_size - 1)]
			gsize copy_size = (old_size - 1) - remove_indexs[remove_size - 1];
			GMemCopy(data + size,
				m_pData + remove_indexs[remove_size - 1] + 1,
				sizeof(T) * copy_size);
			size += copy_size;
		}

		// 释放内存
		GDeallocate<T>(m_pData);
		m_pData = data;
		m_nSize = size;
	}
	
	// 销毁数组
	GArrays::DestoryArray<gsize>(remove_indexs, old_size);
	return counter;
}

template <typename T>
GINLINE gvoid GDynamicArray<T>::Destroy()
{
	GArrays::DestoryArray<T>(m_pData, m_nSize);
	m_pData = GNULL;
	m_nSize = 0;
}

template <typename T>
GINLINE T &GDynamicArray<T>::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename T>
GINLINE const T &GDynamicArray<T>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename T>
GINLINE 
T *GDynamicArray<T>::CursorAt(gsize pos)
{
	return m_pData + pos;
}

template <typename T>
GINLINE const T *GDynamicArray<T>::CursorAt(gsize pos) const
{
	return m_pData + pos;
}

template <typename T>
GINLINE gvoid GDynamicArray<T>::RemoveAt(gsize pos)
{
	GASSERT(m_nSize > 0 && pos < m_nSize);
	if (1 == m_nSize)
	{
		// 直接销毁数组
		Destroy();
	}
	else
	{
		m_pData = GArrays::RemoveArrayElementAt<T>(m_pData, m_nSize, pos);
		m_nSize--;
	}
}

template <typename T>
GINLINE GDynamicArray<T> &GDynamicArray<T>::operator=(const GDynamicArray<T> &arr)
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
		m_pData = GArrays::CopyArrayFrom<T>(m_pData, m_nSize, arr.m_pData, arr.m_nSize);
	}
	else
	{
		m_pData = GArrays::CreateArray<T>(arr.m_pData, 0, arr.m_nSize);
	}
	m_nSize = arr.m_nSize;
	return *this;
}

template <typename T>
GINLINE GDynamicArray<T> &GDynamicArray<T>::operator=(GDynamicArray<T> &&arr)
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

template <typename T>
gbool GDynamicArray<T>::operator==(const GDynamicArray<T> &arr)
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

template <typename T>
GINLINE guint GDynamicArray<T>::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::DynamicArray);
}

template <typename T>
GINLINE gbool GDynamicArray<T>::Serialize(GArchive &archive) const
{
	if (!archive.IsInput())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	gsize size = Size();
	archive << size;

	for (gsize i = 0; i < size; i++)
	{
		if (!GSerialize<T>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

template <typename T>
GINLINE gbool GDynamicArray<T>::Deserialize(GArchive &archive)
{
	if (!archive.IsOutput())
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
		if (!GDeserialize<T>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

} // namespace gsystem

#endif // _CORE_DYNAMIC_ARRAY_INLINE_
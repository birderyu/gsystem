// 可变长数组

#ifndef _CSCORE_CSARRAY_H_
#define _CSCORE_CSARRAY_H_

#include "CsObject.h"

template<typename T>
class CsVector;

template <typename T>
class CsArray :public CsObject
{
	friend class CsVector<T>;

public:
	CsArray();
	CsArray(const cs_size_t len);
	CsArray(const cs_size_t len, const T &t);
	CsArray(const CsArray<T> &tArray);
	~CsArray();

	// 当前数组是否可用
	cs_bool Valid() const;

	// 获取数组的长度
	cs_size_t Length() const;

	// 重分配数组的长度
	cs_bool Resize(const cs_size_t len);
	cs_bool Resize(const cs_size_t len, const T &t);

	// 清空数组
	cs_void Clear();

	// 通过下标访问和修改数组元素
	T &operator[](const cs_size_t id);
	T &operator[](const cs_size_t id) const;

	// 移除特定位置的元素
	cs_bool RemoveAt(const cs_size_t id);
	cs_bool RemoveAt(const CsArray<cs_size_t> &ids);

	// 数组是否包含某元素
	cs_bool Contains(const T &t) const;

	// 从src的start位开始，拷贝len个元素，到dst的first位
	static cs_bool ArrayCopy(const CsArray<T> &src, const cs_size_t start, const cs_size_t len,
		CsArray<T> &dst, const cs_size_t first = 0);

private:
	// 只分配内存，不修改其他参数
	cs_bool ReAlloc(const cs_size_t len);
	
	// 获取内存地址
	T *GetMem(const cs_size_t first = 0) const;

	// 注意：以下两个方法，只拷贝内存，即浅拷贝
	// 从pData的start位开始，拷贝len长度的内存到first位
	cs_bool CopyMemFrom(const cs_size_t first, const cs_size_t len,
		const T *pData, const cs_size_t start = 0);

	// 从start位开始，拷贝len长度的内存到pData的first位
	cs_bool CopyMemTo(const cs_size_t start, const cs_size_t len,
		T *pData, const cs_size_t first = 0) const;

	T *m_pData;
	cs_size_t m_nLength;
};

template <typename T>
CsArray<T>::CsArray()
: m_pData(NULL), m_nLength(0)
{

}

template <typename T>
CsArray<T>::CsArray(const cs_size_t len)
: m_pData(NULL), m_nLength(0)
{
	if (!ReAlloc(len))
	{
		return;
	}
	m_nLength = len;
}

template <typename T>
CsArray<T>::CsArray(const cs_size_t len, const T &t)
: m_pData(NULL), m_nLength(0)
{
	if (!ReAlloc(len))
	{
		return;
	}
	m_nLength = len;
	for (cs_size_t i = 0; i < m_nLength; i++)
	{
		m_pData[i] = t;
	}
}

template <typename T>
CsArray<T>::CsArray(const CsArray<T> &tArray)
: m_pData(NULL), m_nLength(0)
{
	cs_size_t len = tArray.Length();
	if (!ReAlloc(len))
	{
		return;
	}
	m_nLength = len;
	for (cs_size_t i = 0; i < m_nLength; i++)
	{
		m_pData[i] = tArray[i];
	}
}

template <typename T>
CsArray<T>::~CsArray()
{
	Clear();
}

template <typename T>
cs_bool CsArray<T>::Valid() const
{
	return m_pData
		&& m_nLength > 0;
}

template <typename T>
cs_size_t CsArray<T>::Length() const
{
	return m_nLength;
}

template <typename T>
cs_bool CsArray<T>::Resize(const cs_size_t len)
{
	if (len <= 0)
	{
		// 直接清空数组
		Clear();
		return true;
	}
	// 重新分配内存
	if (!ReAlloc(len))
	{
		return false;
	}
	m_nLength = len;
	return true;
}

template <typename T>
cs_bool CsArray<T>::Resize(const cs_size_t len, const T &t)
{
	if (len <= 0)
	{
		// 直接清空数组
		Clear();
		return true;
	}
	// 重新分配内存
	if (!ReAlloc(len))
	{
		return false;
	}
	for (cs_size_t i = m_nLength; i < len; i++)
	{
		m_pData[i] = t;
	}
	m_nLength = len;
	return true;
}

template <typename T>
cs_void CsArray<T>::Clear()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	m_nLength = 0;
}

template <typename T>
T &CsArray<T>::operator[](const cs_size_t id)
{
	CS_ASSERT(id < m_nLength);
	return *(m_pData + id);
}

template <typename T>
T &CsArray<T>::operator[](const cs_size_t id) const
{
	CS_ASSERT(id < m_nLength);
	return *(m_pData + id);
}

template <typename T>
cs_bool CsArray<T>::RemoveAt(const cs_size_t id)
{
	if (!Valid())
	{
		return false;
	}
	cs_size_t len = m_nLength - 1;
	if (len < id)
	{
		return false;
	}
	if (len == 0)
	{
		Clear();
		return true;
	}
	T *pData = new T[len];
	if (!pData)
	{
		return false;
	}
	if (CopyMemTo(0, id, pData, 0))
	{
		if (CopyMemTo(id + 1, len - id, pData, id))
		{
			Clear();
			m_pData = pData;
			m_nLength = len;
			return true;
		}
	}
	delete[] pData;
	pData = NULL;
	return false;
}

template <typename T>
cs_bool CsArray<T>::RemoveAt(const CsArray<cs_size_t> &ids)
{
	if (!Valid())
	{
		return false;
	}
	cs_size_t *keep_ids = new cs_size_t[m_nLength];
	cs_size_t keep_len = 0;
	if (!keep_ids)
	{
		return false;
	}
	for (cs_size_t i = 0; i < m_nLength; i++)
	{
		if (!ids.Contains(i))
		{
			keep_ids[keep_len++] = i;
		}
	}
	T *pData = new T[keep_len];
	if (!pData)
	{
		delete[] keep_ids;
		keep_ids = NULL;
		return false;
	}

	for (cs_size_t i = 0; i < keep_len; i++)
	{
		if (!CopyMemTo(keep_ids[i], 1, pData, i))
		{
			delete[] keep_ids;
			keep_ids = NULL;
			delete[] pData;
			pData = NULL;
			return false;
		}
	}
	delete[] keep_ids;
	keep_ids = NULL;
	Clear();
	m_pData = pData;
	m_nLength = keep_len;
	return true;
}

template <typename T>
cs_bool CsArray<T>::Contains(const T &t) const
{
	if (!m_pData || m_nLength <= 0)
	{
		return false;
	}
	for (cs_size_t i = 0; i < m_nLength; i++)
	{
		if (m_pData[i] == t)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
cs_bool CsArray<T>::ReAlloc(const cs_size_t len)
{
	if (len <= 0)
	{
		// 内存数不大于0，分配失败
		return false;
	}
	if (len == m_nLength)
	{
		// 内存数等于原先的内存，不需要重新分配
		return true;
	}

	T *pData = NULL;
	try
	{
		pData = new T[len];
	}
	catch (std::bad_alloc&)
	{
		pData = NULL;
	}
	if (!pData)
	{
		return false;
	}
	if (m_pData)
	{
		// 备份内存，若len < m_nLength，则很可能发生内存泄露
		cs_size_t backup_len = len < m_nLength ? len : m_nLength;
		if (!CopyMemTo(0, backup_len, pData, 0))
		{
			delete[] pData;
			pData = NULL;
			return false;
		}
	}
	Clear();
	m_pData = pData;
	return true;
}

template <typename T>
T *CsArray<T>::GetMem(const cs_size_t first) const
{
	if (!m_pData || first >= m_nLength)
	{
		return NULL;
	}
	return m_pData + first;
}

template <typename T>
cs_bool CsArray<T>::CopyMemFrom(const cs_size_t first, const cs_size_t len,
	const T *pData, const cs_size_t start)
{
	if (!pData || !m_pData
		|| first >= m_nLength || len + first > m_nLength)
	{
		return false;
	}
	memcpy(m_pData + first, pData + start, sizeof(T) * len);
	return true;
}

template <typename T>
cs_bool CsArray<T>::CopyMemTo(const cs_size_t start, const cs_size_t len,
	T *pData, const cs_size_t first = 0) const
{
	if (!pData || !m_pData
		|| start >= m_nLength || len + start > m_nLength)
	{
		return false;
	}
	memcpy(pData + first, m_pData + start, sizeof(T)* len);
	return true;
}

template <typename T>
cs_bool CsArray<T>::ArrayCopy(const CsArray<T> &src, const cs_size_t start, const cs_size_t len,
	CsArray<T> &dst, const cs_size_t first)
{
	if (len + start > src.Length())
	{
		return false;
	}
	if (len + first > dst.Length())
	{
		dst.Resize(len + first);
	}
	//return src.CopyDataTo(dst.GetData() + first, start, len);
	for (cs_size_t i = start, cs_size_t j = first;
		i < len + start; i++, j++)
	{
		dst[j] = src[i];
	}
}

#endif // _CSCORE_CSARRAY_H_
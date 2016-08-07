#ifndef _CSCORE_CSARRAY_H_
#define _CSCORE_CSARRAY_H_

#include "CsObject.h"

template <typename T>
class CsArray :public CsObject
{
public:
	CsArray();
	CsArray(const cs_size_t len, const T &t = T());
	CsArray(const CsArray<T> &tArray);
	~CsArray();
	cs_size_t Length() const;
	cs_bool ReSize(cs_size_t length);
	void Clear();
	T &operator[](const cs_size_t id);
	const T &operator[](const cs_size_t id) const;
	T *GetData(const cs_size_t start = 0) const;
	T *CopyData(const cs_size_t start, const cs_size_t length) const;
	cs_bool CopyDataTo(T *pData, const cs_size_t start, const cs_size_t length) const;
	cs_bool RemoveAt(const cs_size_t id);
	cs_bool RemoveAt(const CsArray<cs_size_t> &ids);
	cs_bool Contains(const T &t) const;

private:
	T *m_pData;
	cs_size_t m_nLength;
};

template <typename T>
CsArray<T>::CsArray()
: m_pData(NULL), m_nLength(0)
{

}

template <typename T>
CsArray<T>::CsArray(const cs_size_t len, const T &t = T())
: m_pData(NULL), m_nLength(0)
{
	if (len <= 0)
	{
		return;
	}
	try
	{
		m_pData = new T[len];
	}
	catch (std::bad_alloc&)
	{
		m_pData = NULL;
	}
	if (!m_pData)
	{
		return;
	}
	m_nLength = len;
	for (cs_size_t i = 0; i < len; i++)
	{
		m_pData[i] = t;
	}
}

template <typename T>
CsArray<T>::CsArray(const CsArray<T> &tArray)
: m_pData(tArray.CopyData(0, tArray.Length()))
, m_nLength(tArray.Length())
{
	
}

template <typename T>
CsArray<T>::~CsArray()
{
	Clear();
}

template <typename T>
cs_size_t CsArray<T>::Length() const
{
	return m_nLength;
}

template <typename T>
cs_bool CsArray<T>::ReSize(cs_size_t len)
{
	if (len <= m_nLength)
	{
		return false;
	}
	T *pData = new T[len];
	if (!pData)
	{
		return false;
	}

	if (m_pData && m_nLength > 0)
	{
		// back-up
		CopyDataTo(pData, 0, m_nLength);
	}

	Clear();
	m_pData = pData;
	m_nLength = len;
	return true;
}

template <typename T>
void CsArray<T>::Clear()
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
	return *(m_pData + id);
}

template <typename T>
const T &CsArray<T>::operator[](const cs_size_t id) const
{
	return *(m_pData + id);
}

template <typename T>
T *CsArray<T>::GetData(const cs_size_t start) const
{
	if (!m_pData || start >= m_nLength)
	{
		return NULL;
	}
	return m_pData + start;
}

template <typename T>
T *CsArray<T>::CopyData(const cs_size_t start, const cs_size_t len) const
{
	if (!m_pData || start >= m_nLength || len + start > m_nLength)
	{
		return NULL;
	}
	T *pData = new T[len];
	if (!CopyDataTo(pData, start, len))
	{
		if (pData)
		{
			delete[] pData;
			pData = NULL;
		}
		return NULL;
	}
	return pData;
}

template <typename T>
cs_bool CsArray<T>::CopyDataTo(T *pData, const cs_size_t start, const cs_size_t len) const
{
	if (!pData || !m_pData || start >= m_nLength || len + start > m_nLength)
	{
		return false;
	}
	memcpy(pData, m_pData + start, sizeof(T) * len);
	return true;
}

template <typename T>
cs_bool CsArray<T>::RemoveAt(const cs_size_t id)
{
	cs_size_t len = m_nLength - 1;
	if (len < 0 || len < id)
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
	if (CopyDataTo(pData, 0, id))
	{
		if (CopyDataTo(pData + id, id + 1, len - id))
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
	if (!m_pData || m_nLength <= 0)
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
		if (!CopyDataTo(pData + i, keep_ids[i], 1))
		{
			delete[] keep_ids;
			keep_ids = NULL;
			delete[] pData;
			pData = false;
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

#endif // _CSCORE_CSARRAY_H_
#ifndef _CSCORE_CSARRAY_H_
#define _CSCORE_CSARRAY_H_

#include "CsObject.h"

/// 可变长模板数组
template <typename T>
class CsArray :public CsObject
{
public:
	CsArray();
	~CsArray();
	cs_size_t Length() const;
	cs_bool ReSize(cs_size_t nSize);
	void Release();
	T &At(const cs_size_t nSize) const;
	T &operator[](const cs_size_t nSize) const;
	T *Data() const;

private:
	T *m_pData;
	cs_size_t m_nLength;
};

template <typename T>
CsArray<T>::~CsArray()
{
	Release();
}

template <typename T>
CsArray<T>::CsArray()
: m_pData(NULL), m_nSize(0)
{

}

template <typename T>
cs_size_t CsArray<T>::Length() const
{
	return m_nSize;
}

template <typename T>
cs_bool CsArray<T>::ReSize(cs_size_t nSize)
{
	if (!m_pData)
	{
		m_pData = (T*)malloc(nSize * nSize);
	}
	else
	{
		T *pData = (T*)malloc(nSize * nSize);
		if (pData)
		{
			Release();
			memcpy(m_pData, pData, nSize);
		}
	}

	if (m_pData)
	{
		m_nSize = nSize;
		return true;
	}
	m_nSize = 0;
	return false;
}

template <typename T>
void CsArray<T>::Release()
{
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}
	m_nSize = 0;
}

template <typename T>
T &CsArray<T>::At(const cs_size_t nSize) const
{
	return m_pData[nSize];
}

template <typename T>
T &CsArray<T>::operator[](const cs_size_t nSize) const
{
	return At(nSize);
}

template <typename T>
T *CsArray<T>::Data() const
{
	return m_pData;
}

#endif // _CSCORE_CSARRAY_H_
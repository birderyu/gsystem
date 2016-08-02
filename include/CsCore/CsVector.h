#ifndef _CSCORE_CSVECTOR_H_
#define _CSCORE_CSVECTOR_H_

#include "CsArray.h"

#define CS_DEFAULT_VECTOR_SIZE			5
#define CS_DEFAULT_VECTOR_CAPACITY		0.5

template <typename T>
class CsVector :public CsObject
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

public:
	CsVector();
	explicit CsVector(cs_size_t size);
	~CsVector();
	Iterator Begin();
	ConstIterator CBegin() const;
	Iterator End();
	ConstIterator CEnd() const;
	cs_size_t Size() const;

private:
	CsArray<T> m_tArray;
	cs_size_t m_nSize;
};

template <typename T>
CsVector<T>::CsVector()
:m_nSize(CS_DEFAULT_VECTOR_SIZE)
{
	m_tArray.ReSize(CS_DEFAULT_VECTOR_SIZE * (1 + CS_DEFAULT_VECTOR_CAPACITY));
}

template <typename T>
CsVector<T>::CsVector(cs_size_t size)
:m_nSize(size)
{
	m_tArray.ReSize(size * (1 + CS_DEFAULT_VECTOR_CAPACITY));
}

template <typename T>
cs_size_t CsVector<T>::Size() const
{
	return m_nSize;
}

template <typename T>
CsVector<T>::Iterator CsVector<T>::Begin()
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	return m_tArray.Data();
}

template <typename T>
CsVector<T>::ConstIterator CsVector<T>::CBegin() const
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	return m_tArray.Data();
}

template <typename T>
CsVector<T>::Iterator CsVector<T>::End()
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	return m_tArray.Data() + m_nSize;
}

template <typename T>
CsVector<T>::ConstIterator CsVector<T>::CEnd() const
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	return m_tArray.Data() + m_nSize;
}

#endif // _CSCORE_CSVECTOR_H_

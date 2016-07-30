#ifndef _CSCORE_CSVECTOR_H_
#define _CSCORE_CSVECTOR_H_

template <typename T>
class CsVector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

public:
	CsVector();
	~CsVector();
	Iterator Begin();
	ConstIterator CBegin();
	Iterator End();
	ConstIterator CEnd();

private:
	T *m_pData;
	cs_uint m_nCount;
};

template <typename T>
CsVector::CsVector()
:m_nCount(0),
m_pData(NULL)
{
	
}

template <typename T>
CsVector::~CsVector()
{
	if (m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}
}

template <typename T>
CsVector::Iterator CsVector::Begin()
{
	return m_pData;
}

template <typename T>
CsVector::ConstIterator CsVector::CBegin()
{
	return m_pData;
}

template <typename T>
CsVector::Iterator CsVector::End()
{
	if (!m_pData)
	{
		return m_pData
	}
	return m_pData + m_nCount;
}

template <typename T>
CsVector::ConstIterator CsVector::CEnd()
{
	if (!m_pData)
	{
		return m_pData
	}
	return m_pData + m_nCount;
}

#endif // _CSCORE_CSVECTOR_H_

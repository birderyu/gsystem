#ifndef _CSCORE_NUMBER_PRIVATE_H_
#define _CSCORE_NUMBER_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsType.h"
#include "CsString.h"

class CsInt32;

template <typename T>
class CsNumber
{
public:
	CsNumber(const T nValue);
	T GetValue() const;
	bool SetValue(const T nValue);
	CsString ToString(cs_int nBase);

	//static CsNumber<T> ValueOf(const GString &sNum);

private:
	T m_nValue;
};

class CsInt32_Private :public CsObject_Private
{
public:
	CsInt32_Private(CsInt32 *pPublic, const cs_int32 nValue);
	inline operator cs_int32() { return m_nNum.GetValue(); }

private:
	CsNumber<cs_int32> m_nNum;
};

template <typename T>
CsNumber<T>::CsNumber(const T nValue)
: m_nValue(nValue)
{

}

template <typename T>
T CsNumber<T>::GetValue() const
{
	return m_nValue;
}

template <typename T>
bool CsNumber<T>::SetValue(const T nValue)
{
	m_nValue = nValue;
	return true;
}

template <typename T>
CsString CsNumber<T>::ToString(cs_int nBase)
{
	return CsString::FromNum(m_nValue, nBase);
}

#endif // _CSCORE_CSNUMBER_PRIVATE_H_
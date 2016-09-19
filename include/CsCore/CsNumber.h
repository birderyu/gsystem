#ifndef _CSCORE_NUMBER_PRIVATE_H_
#define _CSCORE_NUMBER_PRIVATE_H_

#include "CsObject.h"
#include "CsString.h"

template<typename T> class CsNumberT;
typedef CsNumberT<cs_byte> CsByte;
typedef CsNumberT<cs_bool> CsBoolean;
typedef CsNumberT<cs_char> CsCharacter;
typedef CsNumberT<cs_uchar> CsUCharacter;
typedef CsNumberT<cs_wchar> CsWCharacter;
typedef CsNumberT<cs_short> CsShort;
typedef CsNumberT<cs_ushort> CsUShort;
typedef CsNumberT<cs_int> CsInteger;
typedef CsNumberT<cs_uint> CsUInteger;
typedef CsNumberT<cs_long> CsLong;
typedef CsNumberT<cs_ulong> CsULong;
typedef CsNumberT<cs_longlong> CsLongLong;
typedef CsNumberT<cs_ulonglong> CsULongLong;
typedef CsNumberT<cs_float> CsFloat;
typedef CsNumberT<cs_double> CsDouble;
typedef CsNumberT<cs_decimal> CsDecimal;

typedef CsNumberT<cs_int8> CsInt8;
typedef CsNumberT<cs_uint8> CsUInt8;
typedef CsNumberT<cs_int16> CsInt16;
typedef CsNumberT<cs_uint16> CsUInt16;
typedef CsNumberT<cs_int32> CsInt32;
typedef CsNumberT<cs_uint32> CsUInt32;
typedef CsNumberT<cs_int64> CsInt64;
typedef CsNumberT<cs_uint64> CsUInt64;

typedef CsNumberT<cs_real> CsReal;

template <typename T>
class CsNumberT :public CsObject
{
public:
	CsNumberT(const T &nValue = T());
	T &Value();
	T Value() const;
	CsObject *CopyToObject() const;
	cs_uint ClassCode() const;
	CsString ToString(cs_int nBase = 10) const;
	cs_bool Equals(const CsNumberT<T> &nNum);

	//static CsNumber<T> ValueOf(const CsString &sNum);

private:
	T m_nValue;
};

template <typename T>
CsNumberT<T>::CsNumberT(const T &nValue)
: m_nValue(nValue)
{

}

template <typename T>
T &CsNumberT<T>::Value()
{
	return m_nValue;
}

template <typename T>
T CsNumberT<T>::Value() const
{
	return m_nValue;
}

template <typename T>
CsObject *CsNumberT<T>::CopyToObject() const
{
	return new CsNumberT<T>(m_nValue);
}

template <typename T>
cs_uint CsNumberT<T>::ClassCode() const
{
	return CORE_CLASSCODE_NUMBER;
}

template <typename T>
CsString CsNumberT<T>::ToString(cs_int nBase) const
{
	return CsString::FromNum(m_nValue, nBase);
}

template <typename T>
cs_bool CsNumberT<T>::Equals(const CsNumberT<T> &nNum)
{
	return m_nValue == nNum;
}

template <>
cs_bool CsNumberT<cs_float>::Equals(const CsNumberT<cs_float> &nNum)
{
	return false;
}

template <>
cs_bool CsNumberT<cs_double>::Equals(const CsNumberT<cs_double> &nNum)
{
	return false;
}

#endif // _CSCORE_CSNUMBER_PRIVATE_H_
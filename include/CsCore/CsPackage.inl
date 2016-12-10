#ifndef _CORE_PACKAGE_INLINE_
#define _CORE_PACKAGE_INLINE_

template <typename T>
inline CsPackage<T> CsPackage<T>::ValueOf(typename CsPackage<T>::ValueType val)
{
	return CsPackage<T>(val);
}

template <typename T>
inline CsPackage<T>::CsPackage(typename CsPackage<T>::ValueType val)
: m_nValue(val)
{

}

template <typename T>
inline CsPackage<T>::CsPackage(const CsPackage<T> &val)
: m_nValue(val.m_nValue)
{

}

template <typename T>
inline CsPackage<T>::~CsPackage()
{

}

template <typename T>
inline T &CsPackage<T>::Value()
{
	return m_nValue;
}

template <typename T>
inline T CsPackage<T>::Value() const
{
	return m_nValue;
}

template <typename T>
inline CsObjectP CsPackage<T>::Clone() const
{
	return CsObjectP(new CsPackage<T>(m_nValue));
}

template <typename T>
inline const CsObject *CsPackage<T>::Boxing() const
{
	return this;
}

template <typename T>
inline cs_bool CsPackage<T>::Unboxing(const CsObject *pObj)
{
	if (!pObj)
	{
		return false;
	}
	if (pObj == this)
	{
		return true;
	}
	if (pObj->ClassCode() != ClassCode())
	{
		return false;
	}

	const CsPackage<T> *pPackage = dynamic_cast<const CsPackage<T>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	m_nValue = pPackage->m_nValue;
	return true;
}

template <typename T>
inline CsString CsPackage<T>::ToString() const
{
	return CsString::FromNum(m_nValue);
}

template <typename T>
inline CsString CsPackage<T>::ToString(cs_int nBase) const
{
	return CsString::FromNum(m_nValue, nBase);
}

template <typename T>
inline cs_uint CsPackage<T>::ClassCode() const
{
	return CORE_CLASSCODE_PACKAGE;
}

template <typename T>
inline cs_uint CsPackage<T>::HashCode() const
{
	return CsHashing(m_nValue);
}

template <typename T>
inline cs_bool CsPackage<T>::Equals(const CsObject *pObj) const
{
	if (!pObj)
	{
		return false;
	}
	if (pObj == this)
	{
		return true;
	}
	if (pObj->ClassCode() != ClassCode())
	{
		return false;
	}

	const CsPackage<T> *pPackage = dynamic_cast<const CsPackage<T>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	return m_nValue == pPackage->m_nValue;
}

template <typename T>
inline cs_bool CsPackage<T>::Equals(typename CsPackage<T>::ValueType val) const
{
	return m_nValue == val;
}

template <typename T>
inline cs_bool CsPackage<T>::Equals(const CsPackage<T> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename T>
inline cs_bool CsPackage<T>::Serialize(CsBytes &bytes) const
{
	cs_size_t len = bytes.Length();
	bytes << m_nValue;
	return bytes.Length() - len == sizeof(T);
}

template <typename T>
inline cs_bool CsPackage<T>::Deserialize(const CsBytes &bytes)
{
	cs_size_t len = bytes.Length();
	bytes >> m_nValue;
	return len - bytes.Length() == sizeof(T);
}

template <typename T>
inline CsPackage<T> &CsPackage<T>::operator=(typename CsPackage<T>::ValueType val)
{
	m_nValue = val;
	return *this;
}

template <typename T>
inline CsPackage<T> &CsPackage<T>::operator=(const CsPackage<T> &val)
{
	m_nValue = val.m_nValue;
	return *this;
}

template <typename T>
inline cs_bool CsPackage<T>::operator==(typename CsPackage<T>::ValueType val) const
{
	return m_nValue == val;
}

template <typename T>
inline cs_bool CsPackage<T>::operator==(const CsPackage<T> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename T>
inline cs_bool CsPackage<T>::operator!=(typename CsPackage<T>::ValueType val) const
{
	return m_nValue != val;
}

template <typename T>
inline cs_bool CsPackage<T>::operator!=(const CsPackage<T> &val) const
{
	return m_nValue != val.m_nValue;
}

template <typename T>
inline CsNumber<T>::CsNumber(typename CsNumber<T>::ValueType val)
: CsPackage<T>(val)
{

}

template <typename T>
inline CsNumber<T>::CsNumber(const CsNumber<T> &val)
: CsPackage<T>(val)
{

}

template <typename T>
inline CsNumber<T>::~CsNumber()
{

}

template <typename T>
inline cs_uint CsNumber<T>::ClassCode() const
{
	return CORE_CLASSCODE_NUMBER;
}

template <typename T>
inline T CsNumber<T>::operator+(typename CsNumber<T>::ValueType val)
{
	return m_nValue + val;
}

template <typename T>
inline T CsNumber<T>::operator+(const CsNumber<T> &val)
{
	return m_nValue + val.m_nValue;
}

template <typename T>
inline T CsNumber<T>::operator++()
{
	return ++m_nValue;
}

template <typename T>
inline T CsNumber<T>::operator++(cs_int)
{
	return m_nValue++;
}

template <typename T>
inline T CsNumber<T>::operator+=(typename CsNumber<T>::ValueType val)
{
	return m_nValue += val;
}

template <typename T>
inline T CsNumber<T>::operator+=(const CsNumber<T> &val)
{
	return m_nValue += val.m_nValue;
}

template <typename T>
inline T CsNumber<T>::operator-(typename CsNumber<T>::ValueType val)
{
	return m_nValue - val;
}

template <typename T>
inline T CsNumber<T>::operator-(const CsNumber<T> &val)
{
	return m_nValue - val.m_nValue;
}

template <typename T>
inline T CsNumber<T>::operator--()
{
	return --m_nValue;
}

template <typename T>
inline T CsNumber<T>::operator--(cs_int)
{
	return m_nValue--;
}

template <typename T>
inline T CsNumber<T>::operator-=(typename CsNumber<T>::ValueType val)
{
	return m_nValue -= val;
}

template <typename T>
inline T CsNumber<T>::operator-=(const CsNumber<T> &val)
{
	return m_nValue -= val.m_nValue;
}

template <typename T>
inline cs_bool CsNumber<T>::operator>=(typename CsNumber<T>::ValueType val) const
{
	return m_nValue >= val;
}

template <typename T>
inline cs_bool CsNumber<T>::operator>=(const CsNumber<T> &val) const
{
	return m_nValue >= val.m_nValue;
}

template <typename T>
inline cs_bool CsNumber<T>::operator>(typename CsNumber<T>::ValueType val) const
{
	return m_nValue > val;
}

template <typename T>
inline cs_bool CsNumber<T>::operator>(const CsNumber<T> &val) const
{
	return m_nValue > val.m_nValue;
}

template <typename T>
inline cs_bool CsNumber<T>::operator<=(typename CsNumber<T>::ValueType val) const
{
	return m_nValue <= val;
}

template <typename T>
inline cs_bool CsNumber<T>::operator<=(const CsNumber<T> &val) const
{
	return m_nValue <= val.m_nValue;
}

template <typename T>
inline cs_bool CsNumber<T>::operator<(typename CsNumber<T>::ValueType val) const
{
	return m_nValue < val;
}

template <typename T>
inline cs_bool CsNumber<T>::operator<(const CsNumber<T> &val) const
{
	return m_nValue < val.m_nValue;
}

#endif // _CORE_PACKAGE_INLINE_
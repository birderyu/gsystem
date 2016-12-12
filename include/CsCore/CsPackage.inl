#ifndef _CORE_PACKAGE_INLINE_
#define _CORE_PACKAGE_INLINE_

template <typename ValueT>
inline CsPackage<ValueT> CsPackage<ValueT>::ValueOf(typename CsPackage<ValueT>::ValueType val)
{
	return CsPackage<ValueT>(val);
}

template <typename ValueT>
inline CsPackage<ValueT>::CsPackage(typename CsPackage<ValueT>::ValueType val)
: m_nValue(val)
{

}

template <typename ValueT>
inline CsPackage<ValueT>::CsPackage(const CsPackage<ValueT> &val)
: m_nValue(val.m_nValue)
{

}

template <typename ValueT>
inline CsPackage<ValueT>::~CsPackage()
{

}

template <typename ValueT>
inline ValueT &CsPackage<ValueT>::Value()
{
	return m_nValue;
}

template <typename ValueT>
inline ValueT CsPackage<ValueT>::Value() const
{
	return m_nValue;
}

template <typename ValueT>
inline CsObjectP CsPackage<ValueT>::Clone() const
{
	return CsObjectP(new CsPackage<ValueT>(m_nValue));
}

template <typename ValueT>
inline const CsObject *CsPackage<ValueT>::Boxing() const
{
	return this;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Unboxing(const CsObject *pObj)
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

	const CsPackage<ValueT> *pPackage = dynamic_cast<const CsPackage<ValueT>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	m_nValue = pPackage->m_nValue;
	return true;
}

template <typename ValueT>
inline CsString CsPackage<ValueT>::ToString() const
{
	return CsString::FromNum(m_nValue);
}

template <typename ValueT>
inline CsString CsPackage<ValueT>::ToString(cs_int nBase) const
{
	return CsString::FromNum(m_nValue, nBase);
}

template <typename ValueT>
inline cs_uint CsPackage<ValueT>::ClassCode() const
{
	return CORE_CLASSCODE_PACKAGE;
}

template <typename ValueT>
inline cs_uint CsPackage<ValueT>::HashCode() const
{
	return CsHashing(m_nValue);
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Equals(const CsObject *pObj) const
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

	const CsPackage<ValueT> *pPackage = dynamic_cast<const CsPackage<ValueT>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	return m_nValue == pPackage->m_nValue;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Equals(typename CsPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Equals(const CsPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Serialize(CsBytes &bytes) const
{
	cs_size_t len = bytes.Size();
	bytes << m_nValue;
	return bytes.Size() - len == sizeof(ValueT);
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::Deserialize(CsBytes &bytes)
{
	cs_size_t len = bytes.Size();
	bytes >> m_nValue;
	return len - bytes.Size() == sizeof(ValueT);
}

template <typename ValueT>
inline CsPackage<ValueT> &CsPackage<ValueT>::operator=(typename CsPackage<ValueT>::ValueType val)
{
	m_nValue = val;
	return *this;
}

template <typename ValueT>
inline CsPackage<ValueT> &CsPackage<ValueT>::operator=(const CsPackage<ValueT> &val)
{
	m_nValue = val.m_nValue;
	return *this;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::operator==(typename CsPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::operator==(const CsPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::operator!=(typename CsPackage<ValueT>::ValueType val) const
{
	return m_nValue != val;
}

template <typename ValueT>
inline cs_bool CsPackage<ValueT>::operator!=(const CsPackage<ValueT> &val) const
{
	return m_nValue != val.m_nValue;
}

template <typename ValueT>
inline CsNumber<ValueT>::CsNumber(typename CsNumber<ValueT>::ValueType val)
: CsPackage<ValueT>(val)
{

}

template <typename ValueT>
inline CsNumber<ValueT>::CsNumber(const CsNumber<ValueT> &val)
: CsPackage<ValueT>(val)
{

}

template <typename ValueT>
inline CsNumber<ValueT>::~CsNumber()
{

}

template <typename ValueT>
inline cs_uint CsNumber<ValueT>::ClassCode() const
{
	return CORE_CLASSCODE_NUMBER;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator+(typename CsNumber<ValueT>::ValueType val)
{
	return m_nValue + val;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator+(const CsNumber<ValueT> &val)
{
	return m_nValue + val.m_nValue;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator++()
{
	return ++m_nValue;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator++(cs_int)
{
	return m_nValue++;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator+=(typename CsNumber<ValueT>::ValueType val)
{
	return m_nValue += val;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator+=(const CsNumber<ValueT> &val)
{
	return m_nValue += val.m_nValue;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator-(typename CsNumber<ValueT>::ValueType val)
{
	return m_nValue - val;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator-(const CsNumber<ValueT> &val)
{
	return m_nValue - val.m_nValue;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator--()
{
	return --m_nValue;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator--(cs_int)
{
	return m_nValue--;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator-=(typename CsNumber<ValueT>::ValueType val)
{
	return m_nValue -= val;
}

template <typename ValueT>
inline ValueT CsNumber<ValueT>::operator-=(const CsNumber<ValueT> &val)
{
	return m_nValue -= val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator>=(typename CsNumber<ValueT>::ValueType val) const
{
	return m_nValue >= val;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator>=(const CsNumber<ValueT> &val) const
{
	return m_nValue >= val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator>(typename CsNumber<ValueT>::ValueType val) const
{
	return m_nValue > val;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator>(const CsNumber<ValueT> &val) const
{
	return m_nValue > val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator<=(typename CsNumber<ValueT>::ValueType val) const
{
	return m_nValue <= val;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator<=(const CsNumber<ValueT> &val) const
{
	return m_nValue <= val.m_nValue;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator<(typename CsNumber<ValueT>::ValueType val) const
{
	return m_nValue < val;
}

template <typename ValueT>
inline cs_bool CsNumber<ValueT>::operator<(const CsNumber<ValueT> &val) const
{
	return m_nValue < val.m_nValue;
}

#endif // _CORE_PACKAGE_INLINE_
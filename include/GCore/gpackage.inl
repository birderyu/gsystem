#ifndef _CORE_PACKAGE_INLINE_
#define _CORE_PACKAGE_INLINE_

template <typename ValueT>
inline GPackage<ValueT> GPackage<ValueT>::ValueOf(typename GPackage<ValueT>::ValueType val)
{
	return GPackage<ValueT>(val);
}

template <typename ValueT>
inline GPackage<ValueT>::GPackage(typename GPackage<ValueT>::ValueType val)
: m_nValue(val)
{

}

template <typename ValueT>
inline GPackage<ValueT>::GPackage(const GPackage<ValueT> &val)
: m_nValue(val.m_nValue)
{

}

template <typename ValueT>
inline GPackage<ValueT>::~GPackage()
{

}

template <typename ValueT>
inline ValueT &GPackage<ValueT>::Value()
{
	return m_nValue;
}

template <typename ValueT>
inline ValueT GPackage<ValueT>::Value() const
{
	return m_nValue;
}

template <typename ValueT>
inline GObjectP GPackage<ValueT>::Clone() const
{
	return GObjectP(new GPackage<ValueT>(m_nValue));
}

template <typename ValueT>
inline const GObject *GPackage<ValueT>::Boxing() const
{
	return this;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::Unboxing(const GObject *pObj)
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

	const GPackage<ValueT> *pPackage = dynamic_cast<const GPackage<ValueT>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	m_nValue = pPackage->m_nValue;
	return true;
}

template <typename ValueT>
inline GString GPackage<ValueT>::ToString() const
{
	return GString::FromNum(m_nValue);
}

template <typename ValueT>
inline GString GPackage<ValueT>::ToString(gint nBase) const
{
	return GString::FromNum(m_nValue, nBase);
}

template <typename ValueT>
inline guint GPackage<ValueT>::HashCode() const
{
	return GHashing(m_nValue);
}

template <typename ValueT>
inline guint GPackage<ValueT>::ClassCode() const
{
	return GPackage<ValueT>::CLASS_CODE;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::Equals(const GObject *pObj) const
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

	const GPackage<ValueT> *pPackage = dynamic_cast<const GPackage<ValueT>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	return m_nValue == pPackage->m_nValue;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::Equals(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::Serializable() const
{
	return true;
}

template <typename ValueT>
template <typename ArchiveT>
gbool GPackage<ValueT>::Serialize(ArchiveT &archive) const
{
	archive.PushCode(ClassCode());
	archive << m_nValue;
	return true;
}

template <typename ValueT>
template <typename ArchiveT>
gbool GPackage<ValueT>::Deserialize(ArchiveT &archive)
{
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	archive >> m_nValue;
	return true;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::Equals(const GPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
inline GPackage<ValueT> &GPackage<ValueT>::operator=(typename GPackage<ValueT>::ValueType val)
{
	m_nValue = val;
	return *this;
}

template <typename ValueT>
inline GPackage<ValueT> &GPackage<ValueT>::operator=(const GPackage<ValueT> &val)
{
	m_nValue = val.m_nValue;
	return *this;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::operator==(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::operator==(const GPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::operator!=(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue != val;
}

template <typename ValueT>
inline gbool GPackage<ValueT>::operator!=(const GPackage<ValueT> &val) const
{
	return m_nValue != val.m_nValue;
}

template <typename ValueT>
inline GNumber<ValueT>::GNumber(typename GNumber<ValueT>::ValueType val)
: GPackage<ValueT>(val)
{

}

template <typename ValueT>
inline GNumber<ValueT>::GNumber(const GNumber<ValueT> &val)
: GPackage<ValueT>(val)
{

}

template <typename ValueT>
inline GNumber<ValueT>::~GNumber()
{

}

template <typename ValueT>
inline guint GNumber<ValueT>::ClassCode() const
{
	return GNumber<ValueT>::CLASS_CODE;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator+(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue + val;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator+(const GNumber<ValueT> &val)
{
	return m_nValue + val.m_nValue;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator++()
{
	return ++m_nValue;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator++(gint)
{
	return m_nValue++;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator+=(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue += val;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator+=(const GNumber<ValueT> &val)
{
	return m_nValue += val.m_nValue;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator-(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue - val;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator-(const GNumber<ValueT> &val)
{
	return m_nValue - val.m_nValue;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator--()
{
	return --m_nValue;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator--(gint)
{
	return m_nValue--;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator-=(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue -= val;
}

template <typename ValueT>
inline ValueT GNumber<ValueT>::operator-=(const GNumber<ValueT> &val)
{
	return m_nValue -= val.m_nValue;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator>=(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue >= val;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator>=(const GNumber<ValueT> &val) const
{
	return m_nValue >= val.m_nValue;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator>(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue > val;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator>(const GNumber<ValueT> &val) const
{
	return m_nValue > val.m_nValue;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator<=(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue <= val;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator<=(const GNumber<ValueT> &val) const
{
	return m_nValue <= val.m_nValue;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator<(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue < val;
}

template <typename ValueT>
inline gbool GNumber<ValueT>::operator<(const GNumber<ValueT> &val) const
{
	return m_nValue < val.m_nValue;
}

#endif // _CORE_PACKAGE_INLINE_
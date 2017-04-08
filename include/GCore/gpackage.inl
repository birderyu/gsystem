#ifndef _CORE_PACKAGE_INLINE_
#define _CORE_PACKAGE_INLINE_

#include "gstring.h"
#include "ghash.h"
#include "gsharedpointer.h"
#include "gserialize.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

template <typename ValueT>
GINLINE GPackage<ValueT> GPackage<ValueT>::ValueOf(typename GPackage<ValueT>::ValueType val)
{
	return GPackage<ValueT>(val);
}

template <typename ValueT>
GINLINE GPackage<ValueT>::GPackage(typename GPackage<ValueT>::ValueType val)
: m_nValue(val)
{

}

template <typename ValueT>
GINLINE GPackage<ValueT>::GPackage(const GPackage<ValueT> &val)
: m_nValue(val.m_nValue)
{

}

template <typename ValueT>
GINLINE GPackage<ValueT>::~GPackage()
{

}

template <typename ValueT>
GINLINE ValueT &GPackage<ValueT>::Value()
{
	return m_nValue;
}

template <typename ValueT>
GINLINE ValueT GPackage<ValueT>::Value() const
{
	return m_nValue;
}

template <typename ValueT>
GINLINE GObjectPtr GPackage<ValueT>::Clone() const
{
	return GObjectPtr(new GPackage<ValueT>(m_nValue));
}

template <typename ValueT>
GINLINE const GObject *GPackage<ValueT>::Boxing() const
{
	return this;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::Unboxing(const GObject *pObj)
{
	// TODO
	return false;
}

template <typename ValueT>
GINLINE GString GPackage<ValueT>::ToString() const
{
	return GString::Number(m_nValue);
}

template <typename ValueT>
GINLINE GString GPackage<ValueT>::ToString(gint nBase) const
{
	return GString::Number(m_nValue, nBase);
}

template <typename ValueT>
GINLINE guint GPackage<ValueT>::HashCode() const
{
	return GHashing(m_nValue);
}

template <typename ValueT>
GINLINE guint GPackage<ValueT>::ClassCode() const
{
	return G_ERROR_CLASS_CODE;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::Equals(const GObject *pObj) const
{
	if (!pObj)
	{
		return false;
	}
	if (pObj == this)
	{
		return true;
	}
	const GPackage<ValueT> *pPackage = dynamic_cast<const GPackage<ValueT>*>(pObj);
	if (!pPackage)
	{
		return false;
	}
	return m_nValue == pPackage->m_nValue;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::Equals(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
gbool GPackage<ValueT>::Serialize(GArchive &archive) const
{
	archive.PushCode(ClassCode());
	archive << m_nValue;
	return true;
}

template <typename ValueT>
gbool GPackage<ValueT>::Deserialize(GArchive &archive)
{
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	archive >> m_nValue;
	return true;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::Equals(const GPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
GINLINE GPackage<ValueT> &GPackage<ValueT>::operator=(typename GPackage<ValueT>::ValueType val)
{
	m_nValue = val;
	return *this;
}

template <typename ValueT>
GINLINE GPackage<ValueT> &GPackage<ValueT>::operator=(const GPackage<ValueT> &val)
{
	m_nValue = val.m_nValue;
	return *this;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::operator==(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue == val;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::operator==(const GPackage<ValueT> &val) const
{
	return m_nValue == val.m_nValue;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::operator!=(typename GPackage<ValueT>::ValueType val) const
{
	return m_nValue != val;
}

template <typename ValueT>
GINLINE gbool GPackage<ValueT>::operator!=(const GPackage<ValueT> &val) const
{
	return m_nValue != val.m_nValue;
}

template <typename ValueT>
GINLINE GNumber<ValueT>::GNumber(typename GNumber<ValueT>::ValueType val)
: GPackage<ValueT>(val)
{

}

template <typename ValueT>
GINLINE GNumber<ValueT>::GNumber(const GNumber<ValueT> &val)
: GPackage<ValueT>(val)
{

}

template <typename ValueT>
GINLINE GNumber<ValueT>::~GNumber()
{

}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator+(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue + val;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator+(const GNumber<ValueT> &val)
{
	return m_nValue + val.m_nValue;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator++()
{
	return ++m_nValue;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator++(gint)
{
	return m_nValue++;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator+=(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue += val;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator+=(const GNumber<ValueT> &val)
{
	return m_nValue += val.m_nValue;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator-(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue - val;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator-(const GNumber<ValueT> &val)
{
	return m_nValue - val.m_nValue;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator--()
{
	return --m_nValue;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator--(gint)
{
	return m_nValue--;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator-=(typename GNumber<ValueT>::ValueType val)
{
	return m_nValue -= val;
}

template <typename ValueT>
GINLINE ValueT GNumber<ValueT>::operator-=(const GNumber<ValueT> &val)
{
	return m_nValue -= val.m_nValue;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator>=(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue >= val;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator>=(const GNumber<ValueT> &val) const
{
	return m_nValue >= val.m_nValue;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator>(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue > val;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator>(const GNumber<ValueT> &val) const
{
	return m_nValue > val.m_nValue;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator<=(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue <= val;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator<=(const GNumber<ValueT> &val) const
{
	return m_nValue <= val.m_nValue;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator<(typename GNumber<ValueT>::ValueType val) const
{
	return m_nValue < val;
}

template <typename ValueT>
GINLINE gbool GNumber<ValueT>::operator<(const GNumber<ValueT> &val) const
{
	return m_nValue < val.m_nValue;
}

} // namespace gsystem

#endif // _CORE_PACKAGE_INLINE_
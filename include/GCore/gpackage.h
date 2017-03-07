/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gpackage.h
** @brief	基础类型封装类的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _CORE_PACKAGE_H_
#define _CORE_PACKAGE_H_

#include "gobject.h"
#include "gstring.h"
#include "ghash.h"

template <typename ValueT>
class GPackage 
	: public GObject
{
public:
	typedef typename GTypeTraits<ValueT>::ParameterType ValueType;

public:
	enum { CLASS_CODE = CLASS_CODE_PACKAGE, };

public:
	static GPackage<ValueT> ValueOf(ValueType); 

public:
	GPackage(ValueType);
	GPackage(const GPackage<ValueT> &);
	virtual ~GPackage();

	ValueT &Value();
	ValueT Value() const;

	// 从Object中继承的方法，其中ClassCode和Equals需要再次继承
	GObjectP Clone() const;
	const GObject *Boxing() const;
	gbool Unboxing(const GObject *);
	GString ToString() const;
	GString ToString(gint base) const;
	virtual guint ClassCode() const;
	guint HashCode() const;
	virtual gbool Equals(const GObject *) const;
	gbool Equals(ValueType) const;
	gbool Equals(const GPackage<ValueT> &) const;
	gbool Serializable() const;
	template<typename ArchiveT> gbool Serialize(ArchiveT &) const;
	template<typename ArchiveT> gbool Deserialize(ArchiveT &);

	// 运算符重载
	GPackage<ValueT> &operator=(ValueType);
	GPackage<ValueT> &operator=(const GPackage<ValueT> &);
	gbool operator==(ValueType) const;
	gbool operator==(const GPackage<ValueT> &) const;
	gbool operator!=(ValueType) const;
	gbool operator!=(const GPackage<ValueT> &) const;

protected:
	ValueT m_nValue;
};

template <typename ValueT>
class GNumber 
	: public GPackage<ValueT>
{
public:
	enum { CLASS_CODE = CLASS_CODE_NUMBER, };

public:
	GNumber(ValueType);
	GNumber(const GNumber<ValueT> &);
	virtual ~GNumber();

	virtual guint ClassCode() const;

	// 运算符重载
	ValueT operator+(ValueType);
	ValueT operator+(const GNumber<ValueT> &);
	ValueT operator++();
	ValueT operator++(gint);
	ValueT operator+=(ValueType);
	ValueT operator+=(const GNumber<ValueT> &);
	ValueT operator-(ValueType);
	ValueT operator-(const GNumber<ValueT> &);
	ValueT operator--();
	ValueT operator--(gint);
	ValueT operator-=(ValueType);
	ValueT operator-=(const GNumber<ValueT> &);
	gbool operator>=(ValueType) const;
	gbool operator>=(const GNumber<ValueT> &) const;
	gbool operator>(ValueType) const;
	gbool operator>(const GNumber<ValueT> &) const;
	gbool operator<=(ValueType) const;
	gbool operator<=(const GNumber<ValueT> &) const;
	gbool operator<(ValueType) const;
	gbool operator<(const GNumber<ValueT> &) const;
};

#include "gpackage.inl"

#endif // _CORE_PACKAGE_H_
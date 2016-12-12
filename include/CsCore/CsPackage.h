/****************************************************************************
**
** Supernova
**
** @file	CsPackage.h
** @brief	基础类型封装类的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _CORE_PACKAGE_H_
#define _CORE_PACKAGE_H_

#include "CsObject.h"
#include "CsString.h"
#include "CsBytes.h"
#include "CsHash.h"

template <typename ValueT>
class CsPackage 
	: public CsObject
{
public:
	typedef typename CsTraits<ValueT>::ParameterType ValueType;

public:
	enum { CLASSCODE = CORE_CLASSCODE_PACKAGE, };

public:
	static CsPackage<ValueT> ValueOf(ValueType); 

public:
	CsPackage(ValueType);
	CsPackage(const CsPackage<ValueT> &);
	virtual ~CsPackage();

	ValueT &Value();
	ValueT Value() const;

	// 从Object中继承的方法，其中ClassCode和Equals需要再次继承
	CsObjectP Clone() const;
	const CsObject *Boxing() const;
	cs_bool Unboxing(const CsObject *);
	CsString ToString() const;
	CsString ToString(cs_int base) const;
	virtual cs_uint ClassCode() const;
	cs_uint HashCode() const;
	virtual cs_bool Equals(const CsObject *) const;
	cs_bool Equals(ValueType) const;
	cs_bool Equals(const CsPackage<ValueT> &) const;
	cs_bool Serialize(CsBytes &) const;
	cs_bool Deserialize(CsBytes &);

	// 运算符重载
	CsPackage<ValueT> &operator=(ValueType);
	CsPackage<ValueT> &operator=(const CsPackage<ValueT> &);
	cs_bool operator==(ValueType) const;
	cs_bool operator==(const CsPackage<ValueT> &) const;
	cs_bool operator!=(ValueType) const;
	cs_bool operator!=(const CsPackage<ValueT> &) const;

protected:
	ValueT m_nValue;
};

template <typename ValueT>
class CsNumber 
	: public CsPackage<ValueT>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_NUMBER, };

public:
	CsNumber(ValueType);
	CsNumber(const CsNumber<ValueT> &);
	virtual ~CsNumber();

	virtual cs_uint ClassCode() const;

	// 运算符重载
	ValueT operator+(ValueType);
	ValueT operator+(const CsNumber<ValueT> &);
	ValueT operator++();
	ValueT operator++(cs_int);
	ValueT operator+=(ValueType);
	ValueT operator+=(const CsNumber<ValueT> &);
	ValueT operator-(ValueType);
	ValueT operator-(const CsNumber<ValueT> &);
	ValueT operator--();
	ValueT operator--(cs_int);
	ValueT operator-=(ValueType);
	ValueT operator-=(const CsNumber<ValueT> &);
	cs_bool operator>=(ValueType) const;
	cs_bool operator>=(const CsNumber<ValueT> &) const;
	cs_bool operator>(ValueType) const;
	cs_bool operator>(const CsNumber<ValueT> &) const;
	cs_bool operator<=(ValueType) const;
	cs_bool operator<=(const CsNumber<ValueT> &) const;
	cs_bool operator<(ValueType) const;
	cs_bool operator<(const CsNumber<ValueT> &) const;
};

#include "CsPackage.inl"

#endif // _CORE_PACKAGE_H_
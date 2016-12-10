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

template <typename T>
class CsPackage 
	: public CsObject
{
public:
	typedef typename CsTraits<T>::ParameterType ValueType;

public:
	enum { CLASSCODE = CORE_CLASSCODE_PACKAGE, };

public:
	static CsPackage<T> ValueOf(ValueType); 

public:
	CsPackage(ValueType);
	CsPackage(const CsPackage<T> &);
	virtual ~CsPackage();

	T &Value();
	T Value() const;

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
	cs_bool Equals(const CsPackage<T> &) const;
	cs_bool Serialize(CsBytes &) const;
	cs_bool Deserialize(const CsBytes &);

	// 运算符重载
	CsPackage<T> &operator=(ValueType);
	CsPackage<T> &operator=(const CsPackage<T> &);
	cs_bool operator==(ValueType) const;
	cs_bool operator==(const CsPackage<T> &) const;
	cs_bool operator!=(ValueType) const;
	cs_bool operator!=(const CsPackage<T> &) const;

protected:
	T m_nValue;
};

template <typename T>
class CsNumber 
	: public CsPackage<T>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_NUMBER, };

public:
	CsNumber(ValueType);
	CsNumber(const CsNumber<T> &);
	virtual ~CsNumber();

	virtual cs_uint ClassCode() const;

	// 运算符重载
	T operator+(ValueType);
	T operator+(const CsNumber<T> &);
	T operator++();
	T operator++(cs_int);
	T operator+=(ValueType);
	T operator+=(const CsNumber<T> &);
	T operator-(ValueType);
	T operator-(const CsNumber<T> &);
	T operator--();
	T operator--(cs_int);
	T operator-=(ValueType);
	T operator-=(const CsNumber<T> &);
	cs_bool operator>=(ValueType) const;
	cs_bool operator>=(const CsNumber<T> &) const;
	cs_bool operator>(ValueType) const;
	cs_bool operator>(const CsNumber<T> &) const;
	cs_bool operator<=(ValueType) const;
	cs_bool operator<=(const CsNumber<T> &) const;
	cs_bool operator<(ValueType) const;
	cs_bool operator<(const CsNumber<T> &) const;
};

#include "CsPackage.inl"

#endif // _CORE_PACKAGE_H_
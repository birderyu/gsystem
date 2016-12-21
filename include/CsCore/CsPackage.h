/****************************************************************************
**
** CNova: A quick, micro library of C++
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
#include "CsHash.h"

template <typename ValueT>
class CsPackage 
	: public CsObject
{
public:
	typedef typename CsTraits<ValueT>::ParameterType ValueType;

public:
	enum { CLASS_CODE = CLASS_CODE_PACKAGE, };

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
	cs_bool Serializable() const;
	template<typename ArchiveT> cs_bool Serialize(ArchiveT &) const;
	template<typename ArchiveT> cs_bool Deserialize(ArchiveT &);

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
	enum { CLASS_CODE = CLASS_CODE_NUMBER, };

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
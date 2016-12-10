#ifndef _CORE_FUNCTOR_H_
#define _CORE_FUNCTOR_H_

#include "CsType.h"

/// 一元函数
template<typename ArgType,
	typename ResultType>
struct CsUnaryF
{

};

/// 二元函数
template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct CsBinaryF
{

};

/// 二元函数：小于
template<typename ArgType = void>
struct CsLessF
	: public CsBinaryF<ArgType, ArgType, cs_bool>
{
	cs_bool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

/// 二元函数：比较
template<typename ArgType = void>
struct CsCompareF
	: public CsBinaryF<ArgType, ArgType, cs_int>
{
	cs_int operator()(const ArgType &left, const ArgType &right) const
	{
		if (left < right)
		{
			return -1;
		}
		else if (left > right)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

#endif // _CORE_FUNCTOR_H_
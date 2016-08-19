#ifndef _CORE_TEMPLATE_H_
#define _CORE_TEMPLATE_H_

#include "CsType.h"

template<typename ArgType,
	typename ResultType>
struct CsUnaryF
{

};

template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct CsBinaryF
{
	
};

template<class ArgType = void>
struct CsLessF
	: public CsBinaryF<ArgType, ArgType, cs_bool>
{
	cs_bool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

template<class ArgType = void>
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
#endif
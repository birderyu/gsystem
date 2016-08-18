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
struct CsLess
	: public CsBinaryF<ArgType, ArgType, cs_bool>
{
	cs_bool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

#endif
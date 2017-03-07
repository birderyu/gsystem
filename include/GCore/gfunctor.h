#ifndef _CORE_FUNCTOR_H_
#define _CORE_FUNCTOR_H_

#include "gtype.h"

/// 一元函数
template<typename ArgType,
	typename ResultType>
struct GUnaryF
{
	
};

/// 二元函数
template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct GBinaryF
{

};

/// 二元函数：等于
/// 等于应返回两个状态：等于、不等于
template<typename ArgType = void>
struct GEqualToF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left == right);
	}
};

/// 二元函数：小于
/// 小于应返回两个状态：小于、不小于
template<typename ArgType = void>
struct GLessThanF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

/// 二元函数：大于
/// 大于应返回两个状态：大于、不大于
template<typename ArgType = void>
struct GGreaterThanF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left > right);
	}
};

/// 二元函数：小于等于
/// 小于等于应返回两个状态：小于等于、大于
template<typename ArgType = void>
struct GGreaterThanOrEqualToF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left >= right);
	}
};

/// 二元函数：大于等于
/// 小于等于应返回两个状态：大于等于、小于
template<typename ArgType = void>
struct GLessThanOrEqualToF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left <= right);
	}
};

/// 二元函数：比较
/// 比较应该返回三个状态：大于、等于、小于
template<typename ArgType = void>
struct GCompareToF
	: public GBinaryF<ArgType, ArgType, gint>
{
	gint operator()(const ArgType &left, const ArgType &right) const
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

/// 三元函数
template<typename Arg1Type,
	typename Arg2Type,
	typename Arg3Type,
	typename ResultType>
struct GTernaryF
{

};

/// 三元函数：左开右开区间
template<typename ArgType = void>
struct GLeftOpenRightOpenF
	: public GTernaryF<ArgType, ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &key, const ArgType &left, const ArgType &right) const
	{
		return key > left && key < right;
	}
};

/// 三元函数：左闭右闭区间
template<typename ArgType = void>
struct GLeftClosedRightClosedF
	: public GTernaryF<ArgType, ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &key, const ArgType &left, const ArgType &right) const
	{
		return key >= left && key <= right;
	}
};

/// 三元函数：左开右闭区间
template<typename ArgType = void>
struct GLeftOpenRightClosedF
	: public GTernaryF<ArgType, ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &key, const ArgType &left, const ArgType &right) const
	{
		return key > left && key <= right;
	}
};

/// 三元函数：左闭右开区间
template<typename ArgType = void>
struct GLeftClosedRightOpenF
	: public GTernaryF<ArgType, ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &key, const ArgType &left, const ArgType &right) const
	{
		return key >= left && key < right;
	}
};

#endif // _CORE_FUNCTOR_H_
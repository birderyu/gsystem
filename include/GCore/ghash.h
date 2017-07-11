/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file ghash.h
** @brief 哈希函数
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_HASH_H_
#define _CORE_HASH_H_

#include "gfunctor.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 哈希函数
** @template T 哈希类型
**
********************************************************************************/
template<typename T>
struct GHashF
	: GUnaryF<T, guint>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] v {const T &} 值
	** @return {guint} 哈希码
	**
	** 获取值v的哈希码
	**
	****************************************************************************/
	guint operator()(const T &v) const;
};

} // namespace gsystem

#include "inline/ghash.inl"

#endif // _CORE_HASH_H_
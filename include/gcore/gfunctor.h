/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gfunctor.h
** @brief 仿函数类型
** @author birderyu
** @contact https://github.com/birderyu
** @date 2015-12-31
** @version 1.0.0
**
** 仿函数类型（functor）即重载了函数运算符operator()的类型，仿函数类型的对象，可以使用类似函
** 数调用的方式执行函数运算符，因此被称为仿函数，也叫函数对象。该文件声明了仿函数类型的基类型，
** 并定义几个默认逻辑的仿函数。
**
********************************************************************************/

#ifndef _CORE_FUNCTOR_H_
#define _CORE_FUNCTOR_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 一元函数
** @template ArgType {type} 参数类型
** @template ResultType {type} 返回值类型
**
** 一元函数即只有一个参数的函数，相当于：ResultType foo(ArgType t);
**
********************************************************************************/
template<typename ArgType,
	typename ResultType>
struct GUnaryF
{
	
};

/********************************************************************************
**
** @brief 二元函数
** @template Arg1Type {type} 参数1类型
** @template Arg2Type {type} 参数2类型
** @template ResultType {type} 返回值类型
**
** 二元函数即有两个参数的函数，相当于：ResultType foo(Arg1Type t1, Arg2Type t2);
**
********************************************************************************/
template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct GBinaryF
{

};

/********************************************************************************
**
** @brief 三元函数
** @template Arg1Type {type} 参数1类型
** @template Arg2Type {type} 参数2类型
** @template Arg3Type {type} 参数3类型
** @template ResultType {type} 返回值类型
**
** 三元函数即有三个参数的函数，相当于：ResultType foo(Arg1Type t1, Arg2Type t2, Arg3Type t3);
**
********************************************************************************/
template<typename Arg1Type,
	typename Arg2Type,
	typename Arg3Type,
	typename ResultType>
struct GTernaryF
{

};

/********************************************************************************
**
** @brief 默认的等于函数
** @template T {type} 值类型
**
** 等于函数是一个二元函数，判断两个值是否相等，返回一个布尔值，表示两个状态：等于、不等于
**
********************************************************************************/
template<typename T = gvoid>
struct GEqualToF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若值相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的小于函数
** @template T {type} 值类型
**
** 小于函数是一个二元函数，判断第一个值是否小于第二个值，返回一个布尔值，表示两个状态：小于、不小于
**
********************************************************************************/
template<typename T = gvoid>
struct GLessThanF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若left小于right，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的大于函数
** @template T {type} 值类型
**
** 大于函数是一个二元函数，判断第一个值是否大于第二个值，返回一个布尔值，表示两个状态：大于、不大于
**
********************************************************************************/
template<typename T = gvoid>
struct GGreaterThanF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若left大于right，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的小于等于函数
** @template T {type} 值类型
**
** 小于等于函数是一个二元函数，判断第一个值是否小于等于第二个值，返回一个布尔值，表示两个状态：
** 小于等于、大于
**
********************************************************************************/
template<typename T = gvoid>
struct GLessThanOrEqualToF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若left小于等于right，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的大于等于函数
** @template T {type} 值类型
**
** 大于等于函数是一个二元函数，判断第一个值是否大于等于第二个值，返回一个布尔值，表示两个状态：
** 大于等于、小于
**
********************************************************************************/
template<typename T = gvoid>
struct GGreaterThanOrEqualToF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若left大于等于right，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的比较函数
** @template T {type} 值类型
**
** 比较函数是一个二元函数，用于比较两个值，返回一个整型值，表示三个状态：大于、等于、小于。若第一
** 个值小于第二个值，则返回值小于0；若第一个值等于第二个值，则返回值等于0；若第一个值大于第二个值，
** 则返回值大于0。
**
********************************************************************************/
template<typename T = gvoid>
struct GCompareToF
	: public GBinaryF<T, T, gint>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gint} 若left小于right，则返回值小于0；若left等于right，则返回值等于0；若
	**			left大于right，则返回值大于0。
	**
	****************************************************************************/
	gint operator()(const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的左开右开区间判断函数
** @template T {type} 值类型
**
** 左开右开区间判断函数是一个三元函数，用于比较一个值是否位于另外两个值组成的左开右开区间内，返回
** 一个布尔值，表示两个状态：位于、不位于
**
********************************************************************************/
template<typename T = gvoid>
struct GLeftOpenRightOpenF
	: public GTernaryF<T, T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] key {const T &} 值
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若key位于left和right组成的左开右开中，则返回true，否则返回false
	**
	** 即判断key是否属于区间 (left, right)
	**
	****************************************************************************/
	gbool operator()(const T &key, const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的左闭右闭区间判断函数
** @template T {type} 值类型
**
** 左闭右闭区间判断函数是一个三元函数，用于比较一个值是否位于另外两个值组成的左闭右闭区间内，返回
** 一个布尔值，表示两个状态：位于、不位于
**
********************************************************************************/
template<typename T = void>
struct GLeftClosedRightClosedF
	: public GTernaryF<T, T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] key {const T &} 值
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若key位于left和right组成的左闭右闭区中，则返回true，否则返回false
	**
	** 即判断key是否属于区间 [left, right]
	**
	****************************************************************************/
	gbool operator()(const T &key, const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的左开右闭区间判断函数
** @template T {type} 值类型
**
** 左开右闭区间判断函数是一个三元函数，用于比较一个值是否位于另外两个值组成的左开右闭区间内，返回
** 一个布尔值，表示两个状态：位于、不位于
**
********************************************************************************/
template<typename T = void>
struct GLeftOpenRightClosedF
	: public GTernaryF<T, T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] key {const T &} 值
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若key位于left和right组成的左开右闭中，则返回true，否则返回false
	**
	** 即判断key是否属于区间 (left, right]
	**
	****************************************************************************/
	gbool operator()(const T &key, const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 默认的左闭右开区间判断函数
** @template T {type} 值类型
**
** 左闭右开区间判断函数是一个三元函数，用于比较一个值是否位于另外两个值组成的左闭右开区间内，返回
** 一个布尔值，表示两个状态：位于、不位于
**
********************************************************************************/
template<typename T = gvoid>
struct GLeftClosedRightOpenF
	: public GTernaryF<T, T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] key {const T &} 值
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return {gbool} 若key位于left和right组成的左闭右开中，则返回true，否则返回false
	**
	** 即判断key是否属于区间 [left, right)
	**
	****************************************************************************/
	gbool operator()(const T &key, const T &left, const T &right) const;
};

/********************************************************************************
**
** @brief 快速的等于函数
** @template T {type} 值类型
** @template SIZE {gsize} 值内存字节大小
**
** 通过内存比较的方法快速比较值是否相等
**
********************************************************************************/
template<typename T, gsize SIZE = sizeof(T)>
struct GFastEqualToF
	: public GBinaryF<T, T, gbool>
{
	/****************************************************************************
	**
	** @name operator()
	** @brief 函数运算符
	** @param [in] left {const T &} 值
	** @param [in] right {const T &} 值
	** @return 若值相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator()(const T &left, const T &right) const;
};

} // namespace gsystem

#include "inline/gfunctor.inl"

#endif // _CORE_FUNCTOR_H_
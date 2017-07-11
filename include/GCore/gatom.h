/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gatom.h
** @brief 原子操作帮助类
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_ATOM_H_
#define _CORE_ATOM_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 原子操作帮助类
**
** 原子操作帮助类封装了几个常用的静态原子方法，该类仅支持整形数值的原子操作
**
********************************************************************************/
class GAtom
{
public:
	/****************************************************************************
	**
	** @name CompareAndSwap
	** @brief 静态方法，原子CAS操作（compare-and-swap）
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] comperand {T} 比较值
	** @param [in] exchange {T} 替换值
	** @return {gbool *} 若操作成功，则返回true，否则返回false
	**
	** 将target的值与comperand比较，若相等，则将target的值替换为exchange，否则不做操作。
	** 由于windows下没有提供返回布尔类型的cas函数，因此在windows下其实是先调用了
	** ValuedCompareAndSwap，再比较结果，效率上相比ValuedCompareAndSwap略有下降
	**
	****************************************************************************/
	template<typename T> 
	static gbool CompareAndSwap(T *target, T comperand, T exchange);

	/****************************************************************************
	**
	** @name ValuedCompareAndSwap
	** @brief 静态方法，带返回值的原子CAS操作（valued compare-and-swap）
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] comperand {T} 比较值
	** @param [in] exchange {T} 替换值
	** @return {T} 返回target之前的值
	**
	** 将target的值与comperand比较，若相等，则将target的值替换为exchange，否则不做操作。
	** 返回target之前的旧值
	**
	****************************************************************************/
	template<typename T> 
	static T ValuedCompareAndSwap(T *target, T comperand, T exchange);

	/****************************************************************************
	**
	** @name IncrementAndFetch
	** @brief 静态方法，原子自增操作，返回新值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @return {T} 返回target自增之后的新值
	**
	** 相当于--*target
	**
	****************************************************************************/
	template<typename T> 
	static T IncrementAndFetch(T *target);

	/****************************************************************************
	**
	** @name DecrementAndFetch
	** @brief 静态方法，原子自减操作，返回新值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @return {T} 返回target自减之后的新值
	**
	** 相当于--*target
	**
	****************************************************************************/
	template<typename T> 
	static T DecrementAndFetch(T *target);

	/****************************************************************************
	**
	** @name FetchAndIncrement
	** @brief 静态方法，原子自增操作，返回旧值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @return {T} 返回target自增之前的旧值
	**
	** 相当于*target++
	**
	****************************************************************************/
	template<typename T> 
	static T FetchAndIncrement(T *target);

	/****************************************************************************
	**
	** @name FetchAndDecrement
	** @brief 静态方法，原子自减操作，返回旧值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @return {T} 返回target自减之前的旧值
	**
	** 相当于*target--
	**
	****************************************************************************/
	template<typename T> 
	static T FetchAndDecrement(T *target);

	/****************************************************************************
	**
	** @name FetchAndAdd
	** @brief 静态方法，原子FAA操作（fetch-and-add）
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] value {T} 增加值
	** @return {T} 返回target增加之前的旧值
	**
	** 增加一个值到target，返回target之前的旧值
	**
	****************************************************************************/
	template<typename T> 
	static T FetchAndAdd(T *target, T value);

	/****************************************************************************
	**
	** @name FetchAndSubtract
	** @brief 静态方法，原子FAS操作（fetch-and-subtract）
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] value {T} 删减值
	** @return {T} 返回target删减之前的旧值
	**
	** 从target减去一个值，返回target之前的旧值
	**
	****************************************************************************/
	template<typename T> 
	static T FetchAndSubtract(T *target, T value);

	/****************************************************************************
	**
	** @name Exchange
	** @brief 静态方法，原子交换，返回旧值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] value {T} 交换值
	** @return {T} 返回target交换之前的旧值
	**
	** 将target的值与value交换，返回target之前的旧值
	**
	****************************************************************************/
	template<typename T> 
	static T Exchange(T *target, T value);

	/****************************************************************************
	**
	** @name SetValue
	** @brief 静态方法，原子设置，返回新值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @param [in] value {T} 设置值
	** @return {T} 返回target设置之前的旧值
	**
	** 将target的值设置为value，返回target设置之后的新值，由于各平台没有提供返回新值的原子
	** 交换操作，SetValue其实是使用Exchange来实现的。推荐使用Exchange
	**
	****************************************************************************/
	template<typename T> 
	static T SetValue(T *target, T value);

	/****************************************************************************
	**
	** @name GetValue
	** @brief 静态方法，原子获取值
	** @template T 原子操作的数据类型
	** @param [in] target {T *} 目标值
	** @return {T} 返回target的值
	**
	****************************************************************************/
	template<typename T> 
	static T GetValue(T *target);
};

} // namespace gsystem

#include "inline/gatom.inl"

#endif // _CORE_ATOM_H_
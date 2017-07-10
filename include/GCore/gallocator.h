/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gallocator.h
** @brief 空间分配器
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
** 该文件包含了空间分配器的定义，空间分配器用于分配和释放内存空间。
**
********************************************************************************/
#ifndef _CORE_ALLOCATOR_H_
#define _CORE_ALLOCATOR_H_

#include "gmemory.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @name GAllocate
** @brief 全局内存空间分配
** @template {ClassT} 分配内存空间的类型
** @param [in] n {gsize} 分配内存空间的大小，单位为sizeof(ClassT)个字节（byte）
** @return {ClassT *} 分配内存空间的首地址
**
********************************************************************************/
template <typename ClassT> ClassT *GAllocate(gsize n = 1) GEXCEPT(false);

/********************************************************************************
**
** @name GDeallocate
** @brief 全局内存空间释放
** @template {ClassT} 释放内存空间的类型
** @param [in] ptr {ClassT *} 待释放内存空间的首地址
**
********************************************************************************/
template <typename ClassT> gvoid GDeallocate(ClassT *ptr) GNOEXCEPT;

/********************************************************************************
**
** @name GReallocate
** @brief 全局内存空间重分配
** @template {ClassT} 重分配内存空间的类型
** @param [in] oldptr {ClassT *} 原内存空间的首地址
** @param [in] newsize {gsize} 重分配内存空间的大小，单位为sizeof(ClassT)个字节（byte）
** @return {ClassT *} 重新分配后的内存空间的首地址
**
********************************************************************************/
template <typename ClassT> ClassT *GReallocate(ClassT *oldptr, gsize newsize) GEXCEPT(false);

/********************************************************************************
**
** @brief 一个默认的空间分配器
** @template {ClassT} 分配内存空间的类型
**
** 使用全局的空间分配方法实现的空间分配器
**
********************************************************************************/
template <typename ClassT>
class GAllocator
{
public:
	/****************************************************************************
	**
	** @name Allocate
	** @brief 内存空间分配
	** @template ClassT 分配内存空间的类型
	** @param [in] n {gsize} 分配内存空间的大小，单位为sizeof(ClassT)个字节（byte）
	** @return {ClassT *} 分配内存空间的首地址
	**
	****************************************************************************/
	ClassT *Allocate(gsize n = 1) GEXCEPT(false);

	/****************************************************************************
	**
	** @name Deallocate
	** @brief 内存空间释放
	** @template ClassT 释放内存空间的类型
	** @param [in] ptr {ClassT *} 待释放内存空间的首地址
	**
	****************************************************************************/
	gvoid Deallocate(ClassT *ptr) GNOEXCEPT;

	/****************************************************************************
	**
	** @name Reallocate
	** @brief 全局内存空间重分配
	** @template ClassT 重分配内存空间的类型
	** @param [in] oldptr {ClassT *} 原内存空间的首地址
	** @param [in] newsize {gsize} 重分配内存空间的大小，单位为sizeof(ClassT)个字节（byte）
	** @return {ClassT *} 重新分配后的内存空间的首地址
	**
	****************************************************************************/
	ClassT *Reallocate(ClassT *oldptr, gsize newsize) GEXCEPT(false);
};

} // namespace gsystem

#include "inline/gallocator.inl"

#endif // _CORE_ALLOCATOR_H_

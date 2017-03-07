/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gallocator.h
** @brief	空间分配器
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-24
** @version	0.1
**
** 包含两个操作：
** 分配内存操作：allocate
** 释放内存操作：deallocate
**
****************************************************************************/
#ifndef _CORE_ALLOCATOR_H_
#define _CORE_ALLOCATOR_H_

#include "gmemory.h"
#include <new>

template <typename ClassT> ClassT *GAllocate(gsize n = 1) noexcept(false);
template <typename ClassT> gvoid GDeallocate(ClassT *ptr) noexcept;
template <typename ClassT> ClassT *GReallocate(ClassT *oldptr, gsize newsize) noexcept(false);

#include "gallocator.inl"

#endif // _CORE_ALLOCATOR_H_

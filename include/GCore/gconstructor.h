/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gconstructor.h
** @brief	对象构造器
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-24
** @version	0.1
**
** 包含两个操作：
** 构造对象操作：construct
** 析构对象操作：destruct
** 其中构造对象操作又细分为：
** 默认构造操作：
** 带参数的构造操作：
** 拷贝构造操作：copy construct
** 移动构造操作：move construct
**
****************************************************************************/
#ifndef _CORE_CONSTRUCTOR_H_
#define _CORE_CONSTRUCTOR_H_

#include "gglobal.h"
#include "gtraits.h"

template <typename ClassT> gvoid GConstruct(ClassT *ptr);
template <typename ClassT> gvoid GConstruct(ClassT *ptr, const ClassT &copyable);
template <typename ClassT> gvoid GConstruct(ClassT *ptr, ClassT &&moveable);
template <typename ClassT> gvoid GDestruct(ClassT *ptr);

template <typename ClassT> gvoid GDefaultConstruct(ClassT *ptr);
template <typename ClassT> gvoid GCopyConstruct(ClassT *ptr, const ClassT &copyable);
template <typename ClassT> gvoid GMoveConstruct(ClassT *ptr, ClassT &&moveable);

#include "gconstructor.inl"

#endif // _CORE_CONSTRUCTOR_H_
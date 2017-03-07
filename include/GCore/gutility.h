#ifndef _CORE_UTILITY_H_
#define _CORE_UTILITY_H_

#include "gtraits.h"

/// 移动语义
template<typename T> typename GRemoveReference<T>::Type &&GMove(T &&t);

/// 完美转发语义
template<typename T> T&& GForward(typename GRemoveReference<T>::Type &t);
template<typename T> T&& GForward(typename GRemoveReference<T>::Type &&t);

/// 交换两个对象，优先使用移动操作
template<typename T> gvoid GSwap(T &a, T &b);

#include "gutility.inl"

#endif // _CORE_UTILITY_H_

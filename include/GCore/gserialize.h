#ifndef _CORE_SERIALIZE_H_
#define _CORE_SERIALIZE_H_

#include "gserializable.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @name	GSerialize
** @brief	全局的序列化方法
**
** 全局的序列化方法，主要用于模板和容器的序列化
**
****************************************************************************/
template<typename DataT>
gbool GSerialize(GArchive &archive, const DataT &v);

/****************************************************************************
**
** @name	GDeserialize
** @brief	全局的反序列化方法
**
** 全局的序列化方法，主要用于模板和容器的反序列化
**
****************************************************************************/
template<typename DataT>
gbool GDeserialize(GArchive &archive, DataT &v);

} // namespace gsystem

#include "inline/gserialize.inl"

#endif // _CORE_SERIALIZE_H_
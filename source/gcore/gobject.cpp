/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file	gobject.cpp
** @brief	基础对象类型的默认实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#include "gobject.h"
#include "gstring.h"
#include "gbytes.h"
#include "gsharedptr.h"

namespace gsystem { // gsystem

GObjectPtr GObject::Clone() const
{
	// 默认情况下，返回一个空指针
	return GObjectPtr();
}

const GObject *GObject::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

gbool GObject::Unboxing(const GObject *)
{
	// 默认情况下，不允许拆箱
	return false;
}

GString GObject::ToString() const
{
	// 默认情况下，返回一个空字符串
	return GString();
}

GBytes GObject::ToBytes() const
{
	// 默认情况下，返回一个空字节串
	return GBytes();
}

guint GObject::HashCode() const
{
	// 默认情况下，返回指针所指地址的数字值
	return (guint)this;
}

gbool GObject::Equals(const GObject &obj) const
{
	return Boxing() == obj.Boxing();
}

} // namespace gsystem

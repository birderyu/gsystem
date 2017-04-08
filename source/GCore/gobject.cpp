/****************************************************************************
**
** GSystem: A quick, micro library of C++
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

GObject::~GObject()
{
	// 析构函数必须定义为虚拟的，并提供一个默认的实现，否则会造成内存泄漏
}

GObjectPtr GObject::Clone() const
{
	// 默认情况下，返回一个空指针
	return GObjectPtr();
}

const GObject *GObject::Boxing() const
{
	// 默认情况下，返回this指针，当继承情况比较复杂时，该方法失效
	return this;
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

gbool GObject::Equals(const GObject *obj) const
{
	// 默认情况下，比较指针数字值
	return this == obj;
}

} // namespace gsystem

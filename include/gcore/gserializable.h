/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gserializable.h
** @brief 序列化接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-4-8
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_SERIALIZABLE_H_
#define _CORE_SERIALIZABLE_H_

#include "gglobal.h"

namespace gsystem { // gsystem
	class GArchive;
} // namespace gsystem

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 序列化接口
**
** 继承该接口并实现了该接口中定义的方法的类，是一个可以被序列化的类
**
********************************************************************************/
class GAPI GSerializable
{
public:
	/****************************************************************************
	**
	** @name ~GSerializable
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GSerializable() = 0 {}

	/****************************************************************************
	**
	** @name ClassCode
	** @brief 返回当前类的类序列号
	** @return {guint} 类序列号
	**
	** 类序列号用于判断类是否一致
	**
	****************************************************************************/
	virtual guint ClassCode() const GNOEXCEPT = 0;

	/****************************************************************************
	**
	** @name ClassName
	** @brief 返回当前类的类名
	** @return {GString} 类名
	**
	****************************************************************************/
	//virtual GString ClassName() const GNOEXCEPT = 0;

	/****************************************************************************
	**
	** @name Serialize
	** @brief 序列化
	** @param [in] archive {GArchive &} 档案
	** @return {gbool} 序列化成功，则返回true，否则返回false
	** @throws GSerializationException
	**
	****************************************************************************/
	virtual gbool Serialize(GArchive &archive) const = 0;

	/****************************************************************************
	**
	** @name Deserialize
	** @brief 反序列化
	** @param [in] archive {GArchive &} 档案
	** @return {gbool} 反序列化成功，则返回true，否则返回false
	** @throws GSerializationException
	**
	****************************************************************************/
	virtual gbool Deserialize(GArchive &archive) = 0;
};

} // namespace gsystem

#endif // _CORE_SERIALIZABLE_H_

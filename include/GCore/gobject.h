/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gobject.h
** @brief	基础对象类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "gtype.h"
#include "gglobal.h"

// 前置声明
namespace gsystem { // gsystem
	class GObject;
	class GString;
	class GBytes;
	template <typename ClassT> class GSharedPointer;
	typedef GSharedPointer<GObject> GObjectPtr;
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	基础对象类型
**
** 基础对象类型是所有资源对象的基类型，对于非资源型对象或内核对象，则不推荐继承该类。
** 认为该类的派生一般具有以下特性：
** 1）可复制，可移动：具有复制构造函数、复制运算符、移动构造函数、移动运算符；
** 2）可以转换为字节串和字符串。
**
****************************************************************************/
class GAPI GObject
{
public:
	enum { 
		CLASS_CODE = CLASS_CODE_OBJECT, ///< GObject的ClassCode
	};

public:
	/****************************************************************************
	**
	** @name	~GObject
	** @brief	析构函数（destructor）
	**
	** 由于GObject需要作为所有资源类的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~GObject() = 0;

	/****************************************************************************
	**
	** @name	Clone
	** @brief	拷贝出一个新的实例
	** @return	{GObjectPtr} 拷贝的新实例，是一个共享指针（GSharedPointer）
	**
	****************************************************************************/
	virtual GObjectPtr Clone() const;

	/****************************************************************************
	**
	** @name	Boxing
	** @brief	封箱
	** @return	{const GObject *} 对当前对象的封箱
	**
	** 封箱操作是将当前对象转换为基础类型的方法，并非创建出新的实例。可以不派生该方法，使用基类的
	** 默认方法，同样可以工作。
	**
	****************************************************************************/
	virtual const GObject *Boxing() const;

	/****************************************************************************
	**
	** @name		Unboxing
	** @brief		拆箱
	** @param[in]	obj {const GObject *} 基础对象的指针
	** @return		{gbool} 拆箱操作是否成功
	**
	** 将一个基础对象的指针拆箱到当前类。可以看成是普通的拷贝运算符。拆箱有可能不成功，即使拆箱
	** 操作成功，也可能会引起部分成员消失。
	**
	****************************************************************************/
	virtual gbool Unboxing(const GObject *obj);

	/****************************************************************************
	**
	** @name	ToString
	** @brief	将当期对象转换为字符串
	** @return	{GString} 转换成的字符串
	**
	****************************************************************************/
	virtual GString ToString() const;

	/****************************************************************************
	**
	** @name	ToBytes
	** @brief	将当期对象转换为字符串
	** @return	{GBytes} 转换成的字符串
	**
	****************************************************************************/
	virtual GBytes ToBytes() const;

	/****************************************************************************
	**
	** @name	ClassCode
	** @brief	获取当前对象的类序列号（ClassCode）
	** @return	{guint} 类序列号
	**
	****************************************************************************/
	virtual guint ClassCode() const;

	/****************************************************************************
	**
	** @name	ClassCode
	** @brief	获取当前对象的哈希码（HashCode）
	** @return	{guint} 哈希码值
	**
	****************************************************************************/
	virtual guint HashCode() const;

	/****************************************************************************
	**
	** @name		Equals
	** @brief		判断对象是否值相等
	** @param[in]	obj {const GObject *} 基础对象的指针
	** @return		{gbool} 若相等，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Equals(const GObject *obj) const;

	/****************************************************************************
	**
	** @name	Serializable
	** @brief	当前对象是否支持序列化
	** @return	{gbool} 若支持序列化，则返回true，否则返回false
	**
	** 若对象支持序列化，则应提供序列化（Serialize）和反序列化（Deserialize）的方法，
	** 这两个方法是模板方法（template），需要传入序列化的档案类（ArchiveT），并需要
	** 模块GSerialization的支持。
	**
	****************************************************************************/
	virtual gbool Serializable() const;

	/****************************************************************************
	**
	** @name		Serialize
	** @brief		序列化
	** @param[out]	archive {ArchiveT &} 归档类
	** @return		{gbool} 序列化是否成功
	**
	** 将当前对象的数据序列化到档案中，需要序列化模块GSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** @name		Deserialize
	** @brief		反序列化
	** @param[in]	archive {ArchiveT &} 归档类
	** @return		{gbool} 反序列化是否成功
	**
	** 将档案反序列化为当前对象的数据，需要序列化模块GSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Deserialize(ArchiveT &archive);
};

} // namespace gsystem

#endif // _CORE_OBJECT_H_

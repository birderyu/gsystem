/****************************************************************************
**
** Supernova: A quick, micro library of C++
**
** @file	CsObject.h
** @brief	基础对象类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		CsObject
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "CsGlobal.h"
#include "CsSharedPointer.h"

class CsObject;
class CsString;
class CsBytes;
typedef CsSharedPointer<CsObject> CsObjectP;

/****************************************************************************
**
** CsObject.h
**
** @class		CsObject
** @brief		基础对象类型
** @module		CsCore
** @property	CLASSCODE
** @method		Clone
** @method		Boxing
** @method		Unboxing
** @method		ToString
** @method		ClassCode
** @method		HashCode
** @method		Equals
** @method		Serialize
** @method		Deserialize
**
** 基础对象类型是所有资源对象的基类型，对于非资源型对象或内核对象，则不推荐继承该类。
**
****************************************************************************/
class CS_API CsObject
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_OBJECT, };

public:
	/****************************************************************************
	**
	** CsObject
	**
	** @name	~CsObject
	** @brief	析构函数（destructor）
	**
	** 由于CsObject需要作为所有资源类的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~CsObject() = 0;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Clone
	** @brief	拷贝出一个新的实例
	** @return	拷贝的新实例，是一个共享指针（CsSharedPointer）
	** @exception
	** @see		CsSharedPointer<T>
	** @see		CsObjectP
	**
	****************************************************************************/
	virtual CsObjectP Clone() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Boxing
	** @brief	封箱
	** @return	对当前对象的封箱
	**
	** 封箱操作是将当前对象转换为基础类型的方法，并非创建出新的实例。
	**
	****************************************************************************/
	virtual const CsObject *Boxing() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Unboxing
	** @brief		拆箱
	** @param[in]	基础对象的指针
	** @return		拆箱操作是否成功
	**
	** 将一个基础对象的指针拆箱到当前类。
	**
	****************************************************************************/
	virtual cs_bool Unboxing(const CsObject *);

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ToString
	** @brief	将当期对象转换为字符串
	** @return	转换成的字符串类型（CsString）
	** @see		CsString
	**
	****************************************************************************/
	virtual CsString ToString() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	获取当前对象的类序列号（ClassCode）
	** @return	类序列号
	**
	****************************************************************************/
	virtual cs_uint ClassCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	获取当前对象的哈希码（HashCode）
	** @return	哈希码值
	**
	****************************************************************************/
	virtual cs_uint HashCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Equals
	** @brief		判断对象是否值相等
	** @param[in]	基础对象的指针
	** @return		若相等，则返回true，否则返回false
	**
	****************************************************************************/
	virtual cs_bool Equals(const CsObject *) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Serialize
	** @brief		序列化
	** @param[out]	字节流
	** @return		序列化是否成功
	** @see			CsBytes
	**
	** 将当前对象的数据序列化到字节流中
	**
	****************************************************************************/
	virtual cs_bool Serialize(CsBytes &) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Deserialize
	** @brief		反序列化
	** @param[in]	字节流
	** @return		反序列化是否成功
	** @see			CsBytes
	**
	** 将字节流反序列化为当前对象的数据
	**
	****************************************************************************/
	virtual cs_bool Deserialize(CsBytes &);
};

#endif // _CORE_OBJECT_H_

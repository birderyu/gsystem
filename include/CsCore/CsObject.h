/****************************************************************************
**
** CNova: A quick, micro library of C++
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

// 类序列号
enum CS_CORE_CLASS_CODE
{
	CLASS_CODE_OBJECT = 0,					// Object

	CLASS_CODE_PACKAGE,						// Package
	CLASS_CODE_NUMBER,						// Number
	CLASS_CODE_BYTE,						// Byte
	CLASS_CODE_BOOLEAN,						// Boolean
	CLASS_CODE_CHARACTER,					// Character
	CLASS_CODE_SIGNED_CHARACTER,			// SignedCharacter
	CLASS_CODE_UNSIGNED_CHARACTER,			// UnsignedCharacter
	CLASS_CODE_WIND_CHARACTER,				// WindCharacter
	CLASS_CODE_SMALL_INTEGER,				// SmallInteger
	CLASS_CODE_UNSIGNED_SMALL_INTEGER,		// UnsignedSmallInteger
	CLASS_CODE_SHORT_INTEGER,				// ShortInteger
	CLASS_CODE_UNSIGNED_SHORT_INTEGER,		// UnsignedShortInteger
	CLASS_CODE_INTEGER,						// Integer
	CLASS_CODE_UNSIGNED_INTEGER,			// UnsignedInteger
	CLASS_CODE_LONG_INTEGER,				// LongInteger
	CLASS_CODE_UNSIGNED_LONG_INTEGER,		// UnsignedLongInteger
	CLASS_CODE_LONG_LONG_INTEGER,			// LongLongInteger
	CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER,	// UnsignedLongLongInteger
	CLASS_CODE_SINGLE_FLOAT,				// SingleFloat
	CLASS_CODE_DOUBLE_FLOAT,				// DoubleFloat
	CLASS_CODE_LONG_DOUBLE_FLOAT,			// LongDoubleFloat

	CLASS_CODE_ARRAY,						// Array
	CLASS_CODE_STATIC_ARRAY,				// StaticArray
	CLASS_CODE_DYNAMIC_ARRAY,				// DynamicArray
	CLASS_CODE_LINKED_LIST,					// LinkedList
	CLASS_CODE_SINGLE_LINKED_LIST,			// SingleLinkedList
	CLASS_CODE_CIRCULAR_LINKED_LIST,		// CircularLinkedList
	CLASS_CODE_DOUBLE_LINKED_LIST,			// DoubleLinkedList
	CLASS_CODE_STACK,						// Stack
	CLASS_CODE_ARRAY_STACK,					// ArrayStack
	CLASS_CODE_LIST_STACK,					// ListStack
	CLASS_CODE_BINARY_TREE,					// BinaryTree
	CLASS_CODE_BINARY_SORT_TREE,			// BinarySortTree

	CLASS_CODE_STRING,						// String
	CLASS_CODE_THREAD,						// Thread
	CLASS_CODE_MUTEX,						// Mutex
	CLASS_CODE_CRITICAL_SECTION,			// CriticalSection

	CLASS_CODE_SOCKET_ADDRESS,				// SockAddress
	CLASS_CODE_SOCKET,						// Socket
	CLASS_CODE_TCPSOCKET,					// TcpSocket
	CLASS_CODE_UDPSOCKET,					// UdpSocket
	CLASS_CODE_VECTOR,						// Vector
	CLASS_CODE_LIST,						// List
	CLASS_CODE_MAP,							// Map
	CLASS_CODE_TABLE,						// Table
	CLASS_CODE_FILE,						// File

	CLASS_CODE_DATE,						// Date
	CLASS_CODE_GEOMETRY,
};

class CsObject;
class CsString;
typedef CsSharedPointer<CsObject> CsObjectP;

/****************************************************************************
**
** CsObject.h
**
** @class		CsObject
** @brief		基础对象类型
** @module		CsCore
**
** 基础对象类型是所有资源对象的基类型，对于非资源型对象或内核对象，则不推荐继承该类。
**
****************************************************************************/
class CS_API CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_OBJECT, };

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
	** @return	{CsObjectP} 拷贝的新实例，是一个共享指针（CsSharedPointer）
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
	** @return	{const CsObject *} 对当前对象的封箱
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
	** @param[in]	obj {const CsObject *} 基础对象的指针
	** @return		{cs_bool} 拆箱操作是否成功
	**
	** 将一个基础对象的指针拆箱到当前类。
	**
	****************************************************************************/
	virtual cs_bool Unboxing(const CsObject *obj);

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ToString
	** @brief	将当期对象转换为字符串
	** @return	{CsString} 转换成的字符串类型（CsString）
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
	** @return	{cs_uint} 类序列号
	**
	****************************************************************************/
	virtual cs_uint ClassCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	获取当前对象的哈希码（HashCode）
	** @return	{cs_uint} 哈希码值
	**
	****************************************************************************/
	virtual cs_uint HashCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Equals
	** @brief		判断对象是否值相等
	** @param[in]	obj {const CsObject *} 基础对象的指针
	** @return		{cs_bool} 若相等，则返回true，否则返回false
	**
	****************************************************************************/
	virtual cs_bool Equals(const CsObject *obj) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Serializable
	** @brief	当前对象是否支持序列化
	** @return	{cs_bool} 若支持序列化，则返回true，否则返回false
	**
	** 若对象支持序列化，则应提供序列化（Serialize）和反序列化（Deserialize）的方法，
	** 这两个方法是模板方法（template），需要传入序列化的档案类（ArchiveT），并需要
	** 模块CsSerialization的支持。
	**
	****************************************************************************/
	virtual cs_bool Serializable() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Serialize
	** @brief		序列化
	** @param[out]	archive {ArchiveT &} 归档类
	** @return		{cs_bool} 序列化是否成功
	** @see			CsArchive
	**
	** 将当前对象的数据序列化到档案中，需要序列化模块CsSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> cs_bool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Deserialize
	** @brief		反序列化
	** @param[in]	archive {ArchiveT &} 归档类
	** @return		{cs_bool} 反序列化是否成功
	** @see			CsArchive
	**
	** 将档案反序列化为当前对象的数据，需要序列化模块CsSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> cs_bool Deserialize(ArchiveT &archive);
};

#endif // _CORE_OBJECT_H_

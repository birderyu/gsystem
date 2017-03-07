/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gobject.h
** @brief	基础对象类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		GObject
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "gglobal.h"
#include "gsharedpointer.h"

G_BEGIN_NAMESPACE
class GObject;
class GString;
class GBytes;
typedef GSharedPointer<GObject> GObjectP;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

// 类序列号
enum G_CLASS_CODE
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

	CLASS_CODE_DATE_TIME,					// DateTime
	CLASS_CODE_DATE,						// Date
	CLASS_CODE_TIME,						// Time
	CLASS_CODE_GEOMETRY,
};

/****************************************************************************
**
** gobject.h
**
** @class		GObject
** @brief		基础对象类型
** @module		GCore
**
** 基础对象类型是所有资源对象的基类型，对于非资源型对象或内核对象，则不推荐继承该类。
** 认为该类的派生一般具有以下特性：
** 1）可复制，可移动：具有复制构造函数、复制运算符、移动构造函数、移动运算符
** 2）可以转换为字节串和字符串
**
****************************************************************************/
class GAPI GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_OBJECT, };

public:
	/****************************************************************************
	**
	** GObject
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
	** GObject
	**
	** @name	Clone
	** @brief	拷贝出一个新的实例
	** @return	{GObjectP} 拷贝的新实例，是一个共享指针（GSharedPointer）
	** @exception
	** @see		GSharedPointer<T>
	** @see		GObjectP
	**
	****************************************************************************/
	virtual GObjectP Clone() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Boxing
	** @brief	封箱
	** @return	{const GObject *} 对当前对象的封箱
	**
	** 封箱操作是将当前对象转换为基础类型的方法，并非创建出新的实例。
	**
	****************************************************************************/
	virtual const GObject *Boxing() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Unboxing
	** @brief		拆箱
	** @param[in]	obj {const GObject *} 基础对象的指针
	** @return		{gbool} 拆箱操作是否成功
	**
	** 将一个基础对象的指针拆箱到当前类。
	**
	****************************************************************************/
	virtual gbool Unboxing(const GObject *obj);

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToString
	** @brief	将当期对象转换为字符串
	** @return	{GString} 转换成的字符串类型（GString）
	** @see		GString
	**
	****************************************************************************/
	virtual GString ToString() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToBytes
	** @brief	将当期对象转换为二进制数组
	** @return	{GBytes} 转换成的二进制数组类型（GBytes）
	** @see		GBytes
	**
	****************************************************************************/
	virtual GBytes ToBytes() const;

	/*
	virtual gbool FromString(const GString &str);
	virtual GBytes ToBytes() const;
	virtual gbool FromBytes(const GBytes &bytes);
	*/

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	获取当前对象的类序列号（ClassCode）
	** @return	{guint} 类序列号
	**
	****************************************************************************/
	virtual guint ClassCode() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	获取当前对象的哈希码（HashCode）
	** @return	{guint} 哈希码值
	**
	****************************************************************************/
	virtual guint HashCode() const;

	/****************************************************************************
	**
	** GObject
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
	** GObject
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
	** GObject
	**
	** @name		Serialize
	** @brief		序列化
	** @param[out]	archive {ArchiveT &} 归档类
	** @return		{gbool} 序列化是否成功
	** @see			GArchive
	**
	** 将当前对象的数据序列化到档案中，需要序列化模块GSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Deserialize
	** @brief		反序列化
	** @param[in]	archive {ArchiveT &} 归档类
	** @return		{gbool} 反序列化是否成功
	** @see			GArchive
	**
	** 将档案反序列化为当前对象的数据，需要序列化模块GSerialization的支持
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Deserialize(ArchiveT &archive);
};

G_END_NAMESPACE

#endif // _CORE_OBJECT_H_

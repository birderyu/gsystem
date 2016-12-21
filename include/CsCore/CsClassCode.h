#ifndef _CORE_CLASS_CODE_H_
#define _CORE_CLASS_CODE_H_

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

#endif // _CORE_CLASS_CODE_H_
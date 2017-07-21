#ifndef _CORE_CLASS_CODE_H_
#define _CORE_CLASS_CODE_H_

#include "gmacro.h"

#ifndef G_FIRST_CLASS_CODE_CORE
#	define G_FIRST_CLASS_CODE_CORE 19910228
#endif // G_FIRST_CLASS_CODE_CORE

#ifndef G_ERROR_CLASS_CODE
#	define G_ERROR_CLASS_CODE G_INT32_MAX
#endif // G_ERROR_CLASS_CODE

namespace gsystem {

enum class GClassCode
{
	Object = G_FIRST_CLASS_CODE_CORE,
	Byte,
	Boolean,
	Character,
	SignedCharacter,
	UnsignedCharacter,
	Character16,
	Character32,
	WindCharacter,
	SmallInteger,
	UnsignedSmallInteger,
	ShortInteger,
	UnsignedShortInteger,
	Integer,
	UnsignedInteger,
	LongInteger,
	UnsignedLongInteger,
	LongLongInteger,
	UnsignedLongLongInteger,
	SingleFloat,
	DoubleFloat,
	LongDoubleFloat,
	DynamicArray,
	SingleLinkedList,
	DoubleLinkedList,
	ArrayStack,
	ListStack,
	ArrayQueue,
	ListQueue,
	BinaryTree,
	BinarySortTree,
	RedBlackTree,
	String,
	StringBuffer,
	StringList,
	Bytes,
	ByteBuffer,
	Vector,
	List,
	OrderMap,
	UnorderMap,
	OrderSet,
	UnorderSet,
	Date,
	Time,
	DateTime,
	Exception,
};

}

#endif // _CORE_CLASS_CODE_H_
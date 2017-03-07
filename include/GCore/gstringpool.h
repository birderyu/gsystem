/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @author	birderyu
** @contact	https://github.com/birderyu
** @file	gstringpool.h
** @date	2016-12-03
** @brief	字符串池类型的定义
**
****************************************************************************/

#ifndef _CORE_STRING_POOL_H_
#define _CORE_STRING_POOL_H_

#include "gglobal.h"
#include "gmemorystore.h"
#include "gvector.h"
#include "gmap.h"

/****************************************************************************
**
** gstringpool.h
**
** @class	GStringPool
** @module	GCore
** @brief	字符串池类型
**
**	为了处理字符串的变长特性，采用多块连续的内存结构去存储和传输字符串：
** 		在字符串池内部，把字符串分为以下几种类型，分别采用以下几种存储方式：
** 1.STRING_POOL_SMALL_STRING：短字符串，长度为1+1+字符串的实际长度（包含'\0'），用一
**   段连续的内存存储，理论上支持的字符串的最大长度为255；
** 2.STRING_POOL_NORMAL_STRING：普通字符串，长度为1+2+字符串的实际长度（包含'\0'），
**   用一段连续的内存存储，支持的字符串的最大长度为65535和（nMaxSize-3）的较小者；
** 3.STRING_POOL_PART_STRING_START：部分字符串的，且位于首位，
**   长度为1+4+G_POINTER_ADDRESS_SIZE+当前部分字符串的长度，理论上支持的字符串的最大
**   长度为4294967295；
** 4.STRING_POOL_PART_STRING_MIDDLE：部分字符串的，且位于中间，
**   长度为1+4+G_POINTER_ADDRESS_SIZE+G_POINTER_ADDRESS_SIZE+当前部分字符串的
**   长度，理论上支持的字符串的最大长度为4294967295；
** 5.STRING_POOL_PART_STRING_END：部分字符串的，且位于结尾，
**   长度为1+4+G_POINTER_ADDRESS_SIZE+当前部分字符串的长度，理论上支持的字符串的最大
**   长度为4294967295；
** 6.STRING_POOL_REFERENCE_STRING：引用字符串，长度为1+G_POINTER_ADDRESS_SIZE，
**   存储另一个字符串的首地址，回收时会重新创建一个全拷贝的副本。
**
****************************************************************************/
class GAPI GStringPool
{
	enum TYPE
	{
		STRING_POOL_SMALL_STRING = 0,
		STRING_POOL_NORMAL_STRING,
		STRING_POOL_PART_STRING_START,
		STRING_POOL_PART_STRING_MIDDLE,
		STRING_POOL_PART_STRING_END,
		STRING_POOL_REFERENCE_STRING,
	};

public:
	GStringPool(gsize nInitSzie = 2048, gsize nMaxSize = 10240);
	gpointer Alloc(gsize);
	gvoid Free(gpointer);

private:
	/// 回收站
	GMap<gsize, GVector<gaddress>> m_tRecycle;
	GMemoryStore m_tStore;
};

#endif // _CORE_STRING_POOL_H_
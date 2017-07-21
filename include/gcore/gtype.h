/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gtype.h
** @brief 全局类型定义
** @author birderyu
** @contact	https://github.com/birderyu
** @date 2015-12-30
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_TYPE_H_
#define _CORE_TYPE_H_

#include "gmacro.h"

#if !defined (time_t) || !defined(ptrdiff_t) || !defined(max_align_t)
#include <cstddef>
#endif

namespace gsystem { // gsystem

/********************************************************************************
**
** @name gchar
** @brief 默认的字符类型
**
********************************************************************************/
typedef	char gchar;

/********************************************************************************
**
** @name gschar
** @brief 默认的有符号字符类型
**
********************************************************************************/
typedef	signed char gschar;

/********************************************************************************
**
** @name guchar
** @brief  默认的无符号字符类型
**
********************************************************************************/
typedef	unsigned char guchar;
typedef char gchar8;		// 8位字符类型
typedef char16_t gchar16;	// 16位字符类型
typedef char32_t gchar32;	// 32位字符类型
typedef	wchar_t gwchar;		// 宽字符类型


typedef	gchar8 *		gstring8;	// 以8位字符为单元的字符串类型
typedef	const gchar8 *	gcstring8;	// 以8位字符为单元的字符串常量类型
typedef	gchar16 *		gstring16;	// 以16位字符为单元的字符串类型
typedef	const gchar16 *	gcstring16;	// 以16位字符为单元的字符串常量类型
typedef	gchar32 *		gstring32;	// 以32位字符为单元的字符串类型
typedef	const gchar32 *	gcstring32;	// 以32位字符为单元的字符串常量类型
typedef	gwchar*			gwstring;	// 以宽字符为单元的字符串类型
typedef	const gwchar*	gcwstring;	// 以宽字符为单元的字符串常量类型

/****************************************************************************
**
** gtype.h
**
** @brief 基本类型
**
****************************************************************************/

typedef	void				gvoid;			// void类型
typedef bool				gbool;			// 布尔类型
typedef short				gshort;			// 短整型
typedef unsigned short		gushort;		// 无符号短整型
typedef int					gint;			// 整型
typedef	unsigned int		guint;			// 无符号整型
typedef long				glong;			// 长整型
typedef	unsigned long		gulong;			// 无符号长整型
typedef float				gfloat;			// 浮点型
typedef double				gdouble;		// 双精度浮点型
#ifdef G_SYSTEM_WINDOWS
typedef __int64				glonglong;		// 长长整型
typedef unsigned __int64	gulonglong;		// 无符号长长整型
typedef long double			glongdouble;	// 扩展精度浮点型
#else // !G_SYSTEM_WINDOWS
typedef long long			glonglong;		// 长长整型
typedef unsigned long long	gulonglong;		// 无符号长长整型
typedef long double			glongdouble;	// 扩展精度浮点型
#endif // !G_SYSTEM_WINDOWS

/****************************************************************************
**
** gtype.h
**
** @brief 自定义类型
**
****************************************************************************/

typedef glongdouble		gdecimal;	// 高精度浮点型
typedef gschar			gsmall;		// 短短整型
typedef guchar			gusmall;	// 无符号短短整型
typedef	gusmall			gbyte;		// 字节类型
typedef	gushort			gword;		// 字类型
typedef gbyte *			gbytes;		// 字节数组类型
typedef const gbyte *	gcbytes;	// 常量字节数组类型
typedef gword *			gwords;		// 字数组类型
typedef const gword *	gcword;		// 常量字数组类型
#ifdef G_REAL_USE_FLOAT
typedef gfloat			greal;		// 实数类型
#else // !G_REAL_USE_FLOAT
typedef gdouble			greal;		// 实数类型
#endif // G_REAL_USE_FLOAT
typedef gsmall			gint8;		// 8位整型
typedef gusmall			guint8;		// 无符号8位整型
typedef gshort			gint16;		// 16位整型
typedef gushort			guint16;	// 无符号16位整型
typedef gint			gint32;		// 32位整型
typedef guint			guint32;	// 无符号32位整型
typedef glonglong		gint64;		// 64位整型
typedef gulonglong		guint64;	// 无符号64位整型

/****************************************************************************
**
** gtype.h
**
** @brief 其他类型
**
****************************************************************************/

typedef	gvoid *			gptr;		// 通用指针类型
typedef	const gvoid *	gcptr;		// 指向常量的通用指针类型
typedef size_t			gsize;		// 长度类型
typedef gsize			gaddress;	// 指针值类型
typedef ptrdiff_t		gptrdiff;	// 指针偏移类型
typedef time_t			gtime;		// 时间戳类型
typedef std::max_align_t		gmaxalign;
typedef nullptr_t		gnullptr;

} // namespace gsystem

#endif // _CORE_TYPE_H_
/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gmacro.h
** @brief	全局宏定义
** @author	birderyu
** @contact	https://github.com/birderyu/GSystem
** @date	2015-12-31
** @version	1.0
**
** 全局宏定义了一些全局的宏，并根据不同操作系统和不同编译器做出相应的调整。
**
****************************************************************************/

#ifndef _CORE_MACRO_H_
#define _CORE_MACRO_H_

/****************************************************************************
**
** 操作系统
** G_SYSTEM_WINDOWS:	Windows
** G_SYSTEM_LINUX:		Linux
**
****************************************************************************/
#if defined (_WIN32) || defined(_WIN64)
/** @brief Windows操作系统 */
# define G_SYSTEM_WINDOWS
#endif // _WIN32 or _WIN64

#ifdef _LINUX
/** @brief Linux操作系统 */
# define G_SYSTEM_LINUX
#endif // _LINUX

/****************************************************************************
**
** 编译器
** G_COMPILER_MSVC: MSVC
** G_COMPILER_GCC: GCC
**
****************************************************************************/
#ifdef _MSC_VER
/** @brief MSVC编译器 */
# define G_COMPILER_MSVC _MSC_VER
#endif // _MSC_VER

#ifdef __GNUC__
/** @brief GCC编译器 */
# define G_COMPILER_GCC
#endif // __GNUC__

#ifdef G_SYSTEM_WINDOWS
#	ifdef _WIN64
#		define G_64_BIT
#	else
#		define G_32_BIT
#	endif // _WIN64
#endif // G_SYSTEM_WINDOWS

// 定义API
#ifdef _DLL
	#define GDLL
#endif // _DLL

#ifdef G_COMPILER_MSVC
#	ifdef GDLL
#		define GAPI __declspec(dllexport)
#	else // !GDLL 
#		define GAPI __declspec(dllimport)
#	endif // GDLL
#else
#	define GAPI
#endif // G_COMPILER_MSVC

//#if __cplusplus >= 201103L
#define G_CXX_11
//#endif

#define GNULL nullptr

#define GNOEXCEPT		noexcept
#define GEXCEPT(x)		noexcept(x)
//#define GNOEXCEPT		throw ()
//#define GEXCEPT(x)

#define G_BEGIN_NAMESPACE	//namespace geonova {
#define G_END_NAMESPACE		//}

#ifdef _DEBUG
#	define GDEBUG
#endif

#ifdef GDEBUG
#	include <assert.h>  
#	define GASSERT(e) assert(e)
#else // !GDEBUG
#	define GASSERT(e) do { } while ((false) && (e))
#endif // GDEBUG

#if defined (i386) || defined (__i386__) || defined (_M_IX86) || \
	defined (vax) || defined (__alpha) || defined (__LITTLE_ENDIAN__) || \
	defined (ARM) || defined (_M_IA64) || defined (_M_AMD64) || \
	defined (__amd64) || \
	((defined (__ia64__) || defined (__ia64)) && !defined (__hpux))
#	define G_LITTLE_ENDIAN 0x0123
#	define G_BYTE_ORDER G_LITTLE_ENDIAN
#else
#	define G_BIG_ENDIAN 0x3210
#	define G_BYTE_ORDER G_BIG_ENDIAN
#endif

#define G_POINTER_ADDRESS_SIZE	sizeof(gsystem::gvoid*)

#define G_INT8_MAX		0x7f
#define G_INT8_MIN		(-0x80)
#define G_UINT8_MAX		0xff

#define G_INT16_MAX		0x7fff
#define G_INT16_MIN		(-0x8000)
#define G_UINT16_MAX	0xffff

#define G_INT32_MAX		0x7fffffff
#define G_INT32_MIN		(-0x7fffffff - 1)
#define G_UINT32_MAX	0xffffffffU

#define G_INT32L_MAX	0x7fffffffL
#define G_INT32L_MIN	(-0x7fffffffL - 1)
#define G_UINT32L_MAX	0xffffffffUL

#define G_INT64_MAX		0x7fffffffffffffffLL
#define G_INT64_MIN		(-0x7fffffffffffffffLL - 1)
#define G_UINT64_MAX	0xffffffffffffffffULL

#define G_LIST_MAX_SIZE (G_UINT32_MAX - 1)
#define G_LIST_NULL_POS G_UINT32_MAX

#ifdef __cplusplus__
extern "C"{
#endif

#ifdef __cplusplus__
}
#endif

#define G_HAS_DECIMAL

#ifndef GINLINE
#	define GINLINE	inline
#endif // !GINLINE

// 字符处理
#define GUCHAR(c)				((gsystem::guchar)(c))
#define G_CHAR_IS_ASCII(c)		(isascii(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALNUM(c)		(isalnum(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALPHA(c)		(isalpha(GUCHAR(c)) != 0)
#define G_CHAR_IS_BLANK(c)		(isblank(GUCHAR(c)) != 0)
#define G_CHAR_IS_CNTRL(c)		(iscntrl(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT(c)		(isdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT_X(c)	(isxdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_GRAPH(c)		(isgraph(GUCHAR(c)) != 0)
#define G_CHAR_IS_LOWER(c)		(islower(GUCHAR(c)) != 0)
#define G_CHAR_IS_PRINT(c)		(isprint(GUCHAR(c)) != 0)
#define G_CHAR_IS_PUNCT(c)		(ispunct(GUCHAR(c)) != 0)
#define G_CHAR_IS_SPACE(c)		(isspace(GUCHAR(c)) != 0)
#define G_CHAR_IS_UPPER(c)		(isupper(GUCHAR(c)) != 0)
#define G_CHAR_TO_LOWER(c)		tolower(GUCHAR(c))
#define G_CHAR_TO_UPPER(c)		toupper(GUCHAR(c))

#define GGBK(cs)	(cs)		// gbk编码
#define GUTF8(cs)	(u8##cs)	// utf-8编码
#define GUTF16(cs)	(u##cs)		// utf-16编码
#define GUTF32(cs)	(U##cs)		// utf-32编码
#define GLOCALE(cs)	(L##cs)		// 

// 常用函数
#define G_CALL_AT_EXIT atexit
#define G_MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define G_MIN(a,b)  (((a) < (b)) ? (a) : (b))

#define G_DATE_SIZE			8
#define G_TIME_SIZE			8
#define G_DATE_TIME_SIZE	(G_DATE_SIZE + G_TIME_SIZE)

// 若需要所有的功能，则应该定义如下的宏
//#define G_NEED_ALL_FUNCTION

#endif // _CORE_MACRO_H_

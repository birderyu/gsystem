#ifndef _CORE_DEFINE_H_
#define _CORE_DEFINE_H_

#if defined(_MSC_VER)
#	define CS_DECL_EXPORT __declspec(dllexport)
#	define CS_DECL_IMPORT __declspec(dllimport)
#endif // _MSC_VER

#ifndef NULL
#	define NULL	0
#endif // !NULL

//#if __cplusplus >= 201103L
#	define CS_CPP_11
//#endif

#ifndef CS_CPP_11
#	define nullptr NULL
#	define override
#	define constexpr
#	define final
#endif // for C++11

#define CS_BEGIN_NAMESPACE namespace CNova {
#define CS_END_NAMESPACE }

#ifdef __cplusplus
#	define CS_DECLARE_NOTHROW  throw()
#endif

#  if defined (CS_CORE_BUILD_DLL)
#    define CNOVA_EXPORT CS_DECL_EXPORT
#  else 
#    define CNOVA_EXPORT CS_DECL_IMPORT
#  endif 
#define CS_API CNOVA_EXPORT

#if defined(_DEBUG)
#	include <assert.h>  
#	define CS_ASSERT(e) assert(e)
#else
#	define CS_ASSERT(e) do { } while ((false) && (e))
#endif // 

#if defined (i386) || defined (__i386__) || defined (_M_IX86) || \
	defined (vax) || defined (__alpha) || defined (__LITTLE_ENDIAN__) || \
	defined (ARM) || defined (_M_IA64) || defined (_M_AMD64) || \
	defined (__amd64) || \
	((defined (__ia64__) || defined (__ia64)) && !defined (__hpux))
#	define CS_LITTLE_ENDIAN 0x0123
#	define CS_BYTE_ORDER CS_LITTLE_ENDIAN
#else
#	define CS_BIG_ENDIAN 0x3210
#	define CS_BYTE_ORDER CS_BIG_ENDIAN
#endif

#define CS_POINTER_ADDRESS_SIZE	4

#define CS_INT8_MAX		0x7f
#define CS_INT8_MIN		(-0x80)
#define CS_UINT8_MAX	0xff

#define CS_INT16_MAX	0x7fff
#define CS_INT16_MIN	(-0x8000)
#define CS_UINT16_MAX	0xffff

#define CS_INT32_MAX	0x7fffffff
#define CS_INT32_MIN	(-0x7fffffff - 1)
#define CS_UINT32_MAX	0xffffffffU

#define CS_INT32L_MAX	0x7fffffffL
#define CS_INT32L_MIN	(-0x7fffffffL - 1)
#define CS_UINT32L_MAX	0xffffffffUL

#define CS_INT64_MAX	0x7fffffffffffffffLL
#define CS_INT64_MIN	(-0x7fffffffffffffffLL - 1)
#define CS_UINT64_MAX	0xffffffffffffffffULL

#define CS_LIST_MAX_SIZE (CS_UINT32_MAX - 1)
#define CS_LIST_NULL_POS CS_UINT32_MAX

#ifdef __cplusplus__
extern "C"{
#endif

#ifdef __cplusplus__
}
#endif

#define CsCallAtExit atexit

#endif // _CORE_DEFINE_H_

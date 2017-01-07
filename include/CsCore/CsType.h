#ifndef _CORE_TYPE_H_
#define _CORE_TYPE_H_

#include "CsDefine.h"

#define CS_HAS_WCHAR
#define CS_HAS_DECIMAL

typedef	void			cs_void;
typedef	void*			cs_pointer;
typedef	const void*		cs_cpointer;

typedef	char			cs_char;
typedef	signed char		cs_schar;
typedef	unsigned char	cs_uchar;
typedef	const cs_char*	cs_cstring;

#ifdef CS_HAS_WCHAR
typedef	wchar_t			cs_wchar;
typedef	const cs_wchar*	cs_cwstring;
#endif // CS_HAS_WCHAR

typedef bool				cs_bool;
typedef short				cs_short;
typedef unsigned short		cs_ushort;
typedef int					cs_int;
typedef	unsigned int		cs_uint;
typedef long				cs_long;
typedef	unsigned long		cs_ulong;
typedef float				cs_float;
typedef double				cs_double;

#ifdef CS_SYSTEM_WINDOWS
#	define CS_HAS_LONG_LONG
#	define CS_HAS_LONG_DOUBLE
	typedef __int64				cs_longlong;
	typedef unsigned __int64	cs_ulonglong;
	typedef long double			cs_longdouble;
#else // !CS_SYSTEM_WINDOWS
#	define CS_HAS_LONG_LONG
#	define CS_HAS_LONG_DOUBLE
	typedef long long			cs_longlong;
	typedef unsigned long long	cs_ulonglong;
	typedef long double			cs_longdouble;
#endif // !CS_SYSTEM_WINDOWS

#ifdef CS_HAS_DECIMAL
	typedef cs_longdouble		cs_decimal;
#endif // CS_HAS_DECIMAL

typedef	cs_uchar		cs_byte;
typedef	cs_ushort		cs_word;

typedef cs_schar		cs_small;
typedef cs_uchar		cs_usmall;

// 实数类型
#ifdef CS_REAL_USE_FLOAT
	typedef cs_float	cs_real;
#else // CS_REAL_USE_DOUBLE
	typedef cs_double	cs_real;
#endif

typedef cs_small		cs_int8;
typedef cs_usmall		cs_uint8;
typedef cs_short		cs_int16;
typedef cs_ushort		cs_uint16;
typedef cs_int			cs_int32;
typedef cs_uint			cs_uint32;
typedef cs_longlong		cs_int64;
typedef cs_ulonglong	cs_uint64;

// 指针地址
typedef cs_uint32 cs_ptr_addr;

typedef size_t cs_size_t;

typedef time_t cs_time_t;

#endif // _CORE_TYPE_H_
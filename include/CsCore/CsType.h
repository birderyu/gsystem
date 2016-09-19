#ifndef _CORE_TYPE_H_
#define _CORE_TYPE_H_

typedef	void			cs_void;
typedef	void*			cs_pointer;
typedef	const void*		cs_cpointer;

typedef	char			cs_char;
typedef	signed char		cs_schar;
typedef	unsigned char	cs_uchar;
typedef	const cs_char*	cs_cstring;
typedef	wchar_t			cs_wchar;
typedef	const cs_wchar*	cs_cwstring;

typedef	unsigned char		cs_byte;
typedef bool				cs_bool;
typedef short				cs_short;
typedef unsigned short		cs_ushort;
typedef int					cs_int;
typedef	unsigned int		cs_uint;
typedef long				cs_long;
typedef	unsigned long		cs_ulong;
#ifdef _WIN32
typedef __int64				cs_longlong;
typedef unsigned __int64	cs_ulonglong;
#else
typedef long long			cs_longlong;
typedef unsigned long long	cs_ulonglong;
#endif
typedef float				cs_float;
typedef double				cs_double;
typedef long double			cs_decimal;

typedef cs_char			cs_int8;
typedef cs_uchar		cs_uint8;
typedef cs_short		cs_int16;
typedef cs_ushort		cs_uint16;
typedef cs_int			cs_int32;
typedef cs_uint			cs_uint32;
typedef cs_longlong		cs_int64;
typedef cs_ulonglong	cs_uint64;

// 实数类型
#ifdef CS_REAL_IS_FLOAT
	typedef cs_float	cs_real;
#else // CS_REAL_IS_DOUBLE
	typedef cs_double	cs_real;
#endif

typedef cs_uint cs_size_t;

/* 64位整型: 字面常量 */
#ifndef INT64_C
#	define INT64_C(c)  c ## LL
#endif

#define	cs_true		true
#define cs_false	false

#endif // _CORE_TYPE_H_
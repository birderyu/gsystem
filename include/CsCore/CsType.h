#ifndef _CSCORE_CSTYPE_H_
#define _CSCORE_CSTYPE_H_

typedef bool			cs_bool;
typedef short			cs_short;
typedef int				cs_int;
typedef long			cs_long;
typedef float			cs_float;
typedef double			cs_double;
typedef long double		cs_decimal;
typedef unsigned short	cs_ushort;
typedef	unsigned int	cs_uint;
typedef	unsigned long	cs_ulong;
typedef	char*			cs_string;
typedef	const char*		cs_ccharptr;
typedef	char*			cs_charptr;
typedef	char			cs_char;
typedef	const char		cs_cchar;
typedef	signed char		cs_schar;
typedef	unsigned char	cs_uchar;
typedef	unsigned char	cs_byte;

typedef unsigned char	cs_uint8;
typedef unsigned short	cs_uint16;
typedef unsigned int	cs_uint32;
typedef char			cs_int8;
typedef short			cs_int16;
typedef int				cs_int32;

typedef double			cs_real;

#ifdef _WIN32
typedef __int64				cs_int64;
typedef unsigned __int64	cs_uint64;
#else
typedef long long			cs_int64;
typedef unsigned long long	cs_uint64;
#endif

typedef unsigned int cs_size_t;

/* 64位整型: 字面常量 */
#ifndef INT64_C
#	define INT64_C(c)  c ## LL
#endif

#define	cs_true		true
#define cs_false	false

#endif // _CSCORE_CSTYPE_H_

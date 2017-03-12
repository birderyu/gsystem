#ifndef _CORE_TYPE_H_
#define _CORE_TYPE_H_

#include "gdefine.h"

#if !defined (time_t) || !defined(ptrdiff_t)
#include <cstddef>
#endif

namespace gnova {

typedef	void			gvoid;
typedef	void*			gpointer;

typedef	char			gchar;
typedef	signed char		gschar;
typedef	unsigned char	guchar;
typedef	const gchar*	gcstring;

typedef gchar		gchar8;
typedef char16_t	gchar16;
typedef char32_t	gchar32;

typedef	const gchar16*	gc16string;
typedef	const gchar32*	gc32string;

typedef	wchar_t			gwchar;
typedef	const gwchar*	gcwstring;

typedef bool				gbool;
typedef short				gshort;
typedef unsigned short		gushort;
typedef int					gint;
typedef	unsigned int		guint;
typedef long				glong;
typedef	unsigned long		gulong;
typedef float				gfloat;
typedef double				gdouble;

#ifdef G_SYSTEM_WINDOWS
	typedef __int64				glonglong;
	typedef unsigned __int64	gulonglong;
	typedef long double			glongdouble;
#else // !G_SYSTEM_WINDOWS
	typedef long long			glonglong;
	typedef unsigned long long	gulonglong;
	typedef long double			glongdouble;
#endif // !G_SYSTEM_WINDOWS

#ifdef G_HAS_DECIMAL
	typedef glongdouble		gdecimal;
#endif // G_HAS_DECIMAL

typedef gschar		gsmall;
typedef guchar		gusmall;
typedef	gsmall		gbyte;
typedef	gushort		gword;


// 实数类型
#ifdef G_REAL_USE_FLOAT
	typedef gfloat	greal;
#else // !G_REAL_USE_FLOAT
	typedef gdouble	greal;
#endif // G_REAL_USE_FLOAT

typedef gsmall		gint8;
typedef gusmall		guint8;
typedef gshort		gint16;
typedef gushort		guint16;
typedef gint		gint32;
typedef guint		guint32;
typedef glonglong	gint64;
typedef gulonglong	guint64;

typedef ptrdiff_t	gaddress;
typedef size_t		gsize;
typedef time_t		gtime;		// 时间戳类型

} // end namespace gnova

#endif // _CORE_TYPE_H_
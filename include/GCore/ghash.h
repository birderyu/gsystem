#ifndef _CORE_HASH_H_
#define _CORE_HASH_H_

#include "gglobal.h"

/// 基本内置类型的Hash算法
GAPI guint GHashing(gbool);
GAPI guint GHashing(gchar);
GAPI guint GHashing(gschar);
GAPI guint GHashing(guchar);
GAPI guint GHashing(gwchar);
GAPI guint GHashing(gshort);
GAPI guint GHashing(gushort);
GAPI guint GHashing(gint);
GAPI guint GHashing(guint);
GAPI guint GHashing(glong);
GAPI guint GHashing(gulong);
GAPI guint GHashing(glonglong);
GAPI guint GHashing(gulonglong);
GAPI guint GHashing(gfloat);
GAPI guint GHashing(gdouble);
GAPI guint GHashing(gdecimal);
GAPI guint GHashing(gpointer);

/// Hash函数
template<typename T>
struct GHashF
	: GUnaryF<T, guint>
{
	guint operator()(const T &v) const
	{
		return v.HashCode();
	}
};

template<>
struct GHashF<gbool>
{
	guint operator()(const gbool &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gchar>
{
	guint operator()(const gchar &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gschar>
{
	guint operator()(const gschar &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<guchar>
{
	guint operator()(const guchar &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gwchar>
{
	guint operator()(const gwchar &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gshort>
{
	guint operator()(const gshort &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gushort>
{
	guint operator()(const gushort &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gint>
{
	guint operator()(const gint &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<guint>
{
	guint operator()(const guint &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<glong>
{
	guint operator()(const glong &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gulong>
{
	guint operator()(const gulong &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<glonglong>
{
	guint operator()(const glonglong &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gulonglong>
{
	guint operator()(const gulonglong &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gfloat>
{
	guint operator()(const gfloat &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gdouble>
{
	guint operator()(const gdouble &v) const
	{
		return GHashing(v);
	}
};

template<>
struct GHashF<gdecimal>
{
	guint operator()(const gdecimal &v) const
	{
		return GHashing(v);
	}
};

template<typename T>
struct GHashF<T*>
{
	guint operator()(const T *v) const
	{
		return GHashing(v);
	}
};

#endif // _CORE_HASH_H_
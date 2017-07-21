#ifndef _CORE_HASH_INLINE_
#define _CORE_HASH_INLINE_

namespace gsystem { // gsystem

/// 基本内置类型的Hash算法
GAPI guint GHashing(gbool value);
GAPI guint GHashing(gchar value);
GAPI guint GHashing(gschar value);
GAPI guint GHashing(guchar value);
GAPI guint GHashing(gchar16 value);
GAPI guint GHashing(gchar32 value);
GAPI guint GHashing(gwchar value);
GAPI guint GHashing(gshort value);
GAPI guint GHashing(gushort value);
GAPI guint GHashing(gint value);
GAPI guint GHashing(guint value);
GAPI guint GHashing(glong value);
GAPI guint GHashing(gulong value);
GAPI guint GHashing(glonglong value);
GAPI guint GHashing(gulonglong value);
GAPI guint GHashing(gfloat value);
GAPI guint GHashing(gdouble value);
GAPI guint GHashing(glongdouble value);
GAPI guint GHashing(gptr value);

template<typename T> GINLINE
guint GHashF<T>::operator()(const T &v) const
{
	return v.HashCode();
}

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

} // namespace gsystem

#endif // _CORE_HASH_INLINE_

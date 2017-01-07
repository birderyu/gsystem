#ifndef _CORE_TRAITS_H_
#define _CORE_TRAITS_H_

#include "gtype.h"

template<typename T>
struct GTraits
{
	typedef const T &ParameterType;
};

template<>
struct GTraits<gbool>
{
	typedef gbool ParameterType;
};

template<>
struct GTraits<gchar>
{
	typedef gchar ParameterType;
};

template<>
struct GTraits<gschar>
{
	typedef gschar ParameterType;
};

template<>
struct GTraits<guchar>
{
	typedef guchar ParameterType;
};

template<>
struct GTraits<gwchar>
{
	typedef gwchar ParameterType;
};

template<>
struct GTraits<gshort>
{
	typedef gshort ParameterType;
};

template<>
struct GTraits<gushort>
{
	typedef gushort ParameterType;
};

template<>
struct GTraits<gint>
{
	typedef gint ParameterType;
};

template<>
struct GTraits<guint>
{
	typedef guint ParameterType;
};

template<>
struct GTraits<glong>
{
	typedef glong ParameterType;
};

template<>
struct GTraits<gulong>
{
	typedef gulong ParameterType;
};

template<>
struct GTraits<glonglong>
{
	typedef glonglong ParameterType;
};

template<>
struct GTraits<gulonglong>
{
	typedef gulonglong ParameterType;
};

template<>
struct GTraits<gfloat>
{
	typedef gfloat ParameterType;
};

template<>
struct GTraits<gdouble>
{
	typedef gdouble ParameterType;
};

template<>
struct GTraits<gdecimal>
{
	typedef gdecimal ParameterType;
};

template<typename T>
struct GTraits<T*>
{
	typedef T* ParameterType;
};

#endif // _CORE_TRAITS_H_
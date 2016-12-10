#ifndef _CORE_TRAITS_H_
#define _CORE_TRAITS_H_

#include "CsType.h"

template<typename T>
struct CsTraits
{
	typedef const T &ParameterType;
};

template<>
struct CsTraits<cs_bool>
{
	typedef cs_bool ParameterType;
};

template<>
struct CsTraits<cs_char>
{
	typedef cs_char ParameterType;
};

template<>
struct CsTraits<cs_schar>
{
	typedef cs_schar ParameterType;
};

template<>
struct CsTraits<cs_uchar>
{
	typedef cs_uchar ParameterType;
};

template<>
struct CsTraits<cs_wchar>
{
	typedef cs_wchar ParameterType;
};

template<>
struct CsTraits<cs_short>
{
	typedef cs_short ParameterType;
};

template<>
struct CsTraits<cs_ushort>
{
	typedef cs_ushort ParameterType;
};

template<>
struct CsTraits<cs_int>
{
	typedef cs_int ParameterType;
};

template<>
struct CsTraits<cs_uint>
{
	typedef cs_uint ParameterType;
};

template<>
struct CsTraits<cs_long>
{
	typedef cs_long ParameterType;
};

template<>
struct CsTraits<cs_ulong>
{
	typedef cs_ulong ParameterType;
};

template<>
struct CsTraits<cs_longlong>
{
	typedef cs_longlong ParameterType;
};

template<>
struct CsTraits<cs_ulonglong>
{
	typedef cs_ulonglong ParameterType;
};

template<>
struct CsTraits<cs_float>
{
	typedef cs_float ParameterType;
};

template<>
struct CsTraits<cs_double>
{
	typedef cs_double ParameterType;
};

template<>
struct CsTraits<cs_decimal>
{
	typedef cs_decimal ParameterType;
};

template<typename T>
struct CsTraits<T*>
{
	typedef T* ParameterType;
};

#endif // _CORE_TRAITS_H_
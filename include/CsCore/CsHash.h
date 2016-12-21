#ifndef _CORE_HASH_H_
#define _CORE_HASH_H_

#include "CsGlobal.h"

CS_API cs_uint CsHashing(cs_bool);
CS_API cs_uint CsHashing(cs_char);
CS_API cs_uint CsHashing(cs_schar);
CS_API cs_uint CsHashing(cs_uchar);
CS_API cs_uint CsHashing(cs_wchar);
CS_API cs_uint CsHashing(cs_short);
CS_API cs_uint CsHashing(cs_ushort);
CS_API cs_uint CsHashing(cs_int);
CS_API cs_uint CsHashing(cs_uint);
CS_API cs_uint CsHashing(cs_long);
CS_API cs_uint CsHashing(cs_ulong);
CS_API cs_uint CsHashing(cs_longlong);
CS_API cs_uint CsHashing(cs_ulonglong);
CS_API cs_uint CsHashing(cs_float);
CS_API cs_uint CsHashing(cs_double);
CS_API cs_uint CsHashing(cs_decimal);
CS_API cs_uint CsHashing(cs_pointer);

/// Hashº¯Êý
template<typename T>
struct CsHashF
	: CsUnaryF<T, cs_uint>
{
	cs_uint operator()(const T &v) const
	{
		return v.HashCode();
	}
};

template<>
struct CsHashF<cs_bool>
{
	cs_uint operator()(const cs_bool &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_char>
{
	cs_uint operator()(const cs_char &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_schar>
{
	cs_uint operator()(const cs_schar &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_uchar>
{
	cs_uint operator()(const cs_uchar &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_wchar>
{
	cs_uint operator()(const cs_wchar &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_short>
{
	cs_uint operator()(const cs_short &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_ushort>
{
	cs_uint operator()(const cs_ushort &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_int>
{
	cs_uint operator()(const cs_int &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_uint>
{
	cs_uint operator()(const cs_uint &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_long>
{
	cs_uint operator()(const cs_long &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_ulong>
{
	cs_uint operator()(const cs_ulong &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_longlong>
{
	cs_uint operator()(const cs_longlong &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_ulonglong>
{
	cs_uint operator()(const cs_ulonglong &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_float>
{
	cs_uint operator()(const cs_float &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_double>
{
	cs_uint operator()(const cs_double &v) const
	{
		return CsHashing(v);
	}
};

template<>
struct CsHashF<cs_decimal>
{
	cs_uint operator()(const cs_decimal &v) const
	{
		return CsHashing(v);
	}
};

#endif // _CORE_HASH_H_
#include "CsHash.h"
#include "CsMath.h"

cs_uint CsHashing(cs_bool val)
{
	if (val)
	{
		return 1;
	}
	return 0;
}

cs_uint CsHashing(cs_char val)
{
	return static_cast<cs_uint>(val);
}

cs_uint CsHashing(cs_schar val)
{
	return static_cast<cs_uint>(val);
}

cs_uint CsHashing(cs_uchar val)
{
	return static_cast<cs_uint>(val);
}

cs_uint CsHashing(cs_wchar)
{
	return 0;
}

cs_uint CsHashing(cs_short)
{
	return 0;
}

cs_uint CsHashing(cs_ushort)
{
	return 0;
}

cs_uint CsHashing(cs_int val)
{
	return val % CS_INT32_MAX;
}

cs_uint CsHashing(cs_uint)
{
	return 0;
}

cs_uint CsHashing(cs_long)
{
	return 0;
}

cs_uint CsHashing(cs_ulong)
{
	return 0;
}

cs_uint CsHashing(cs_longlong)
{
	return 0;
}

cs_uint CsHashing(cs_ulonglong)
{
	return 0;
}

cs_uint CsHashing(cs_float)
{
	return 0;
}

cs_uint CsHashing(cs_double val)
{
	cs_double e = 0;
	cs_double tmp = val;
	if (val < 0)
	{
		tmp = -val;
	}
	e = CsMath::Ceil(CsMath::Log(val));
	return cs_uint((CS_INT64_MAX + 1.0) * tmp * CsMath::Exp(-e));
}

cs_uint CsHashing(cs_decimal)
{
	return 0;
}

cs_uint CsHashing(cs_pointer)
{
	return 0;
}
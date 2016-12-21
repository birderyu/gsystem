#include "CsString.h"
#include <sstream>

template <typename T>
CsString _FromNum(T nNum, cs_int nBase)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << nNum;
	return CsString(oss.str().c_str());
}

template <typename T>
T _ToNum(const CsString &str, cs_bool *isok)
{
	std::istringstream iss(str.CString());
	T nNum;
	if (isok) *isok = false;

	if (iss >> nNum)
	{
		if (isok) *isok = true;
	}
	return nNum;
}

CsString CsString::FromNum(cs_small nNum, cs_int nBase)
{
	return _FromNum<cs_small>(nNum, nBase);
}

CsString CsString::FromNum(cs_usmall nNum, cs_int nBase)
{
	return _FromNum<cs_usmall>(nNum, nBase);
}

CsString CsString::FromNum(cs_short nNum, cs_int nBase)
{
	return _FromNum<cs_short>(nNum, nBase);
}

CsString CsString::FromNum(cs_ushort nNum, cs_int nBase)
{
	return _FromNum<cs_ushort>(nNum, nBase);
}

CsString CsString::FromNum(cs_int nNum, cs_int nBase)
{
	return _FromNum<cs_int>(nNum, nBase);
}

CsString CsString::FromNum(cs_uint nNum, cs_int nBase)
{
	return _FromNum<cs_uint>(nNum, nBase);
}

CsString CsString::FromNum(cs_long nNum, cs_int nBase)
{
	return _FromNum<cs_long>(nNum, nBase);
}

CsString CsString::FromNum(cs_ulong nNum, cs_int nBase)
{
	return _FromNum<cs_ulong>(nNum, nBase);
}

CsString CsString::FromNum(cs_longlong nNum, cs_int nBase)
{
	return _FromNum<cs_longlong>(nNum, nBase);
}

CsString CsString::FromNum(cs_ulonglong nNum, cs_int nBase)
{
	return _FromNum<cs_ulonglong>(nNum, nBase);
}

CsString CsString::FromNum(cs_float nNum, cs_int nBase)
{
	return _FromNum<cs_float>(nNum, nBase);
}

CsString CsString::FromNum(cs_double nNum, cs_int nBase)
{
	return _FromNum<cs_double>(nNum, nBase);
}

CsString CsString::FromNum(cs_decimal nNum, cs_int nBase)
{
	return _FromNum<cs_decimal>(nNum, nBase);
}

cs_small CsString::ToSmall(cs_bool *bIsOk) const
{
	return _ToNum<cs_small>(*this, bIsOk);
}

cs_usmall CsString::ToUSmall(cs_bool *bIsOk) const
{
	return _ToNum<cs_usmall>(*this, bIsOk);
}

cs_short CsString::ToShort(cs_bool *bIsOk) const
{
	return _ToNum<cs_short>(*this, bIsOk);
}

cs_ushort CsString::ToUShort(cs_bool *bIsOk) const
{
	return _ToNum<cs_ushort>(*this, bIsOk);
}

cs_int CsString::ToInt(cs_bool *bIsOk) const
{
	return _ToNum<cs_int>(*this, bIsOk);
}

cs_uint CsString::ToUInt(cs_bool *bIsOk) const
{
	return _ToNum<cs_uint>(*this, bIsOk);
}

cs_long CsString::ToLong(cs_bool *bIsOk) const
{
	return _ToNum<cs_long>(*this, bIsOk);
}

cs_ulong CsString::ToULong(cs_bool *bIsOk) const
{
	return _ToNum<cs_ulong>(*this, bIsOk);
}

cs_longlong CsString::ToLongLong(cs_bool *bIsOk) const
{
	return _ToNum<cs_longlong>(*this, bIsOk);
}

cs_ulonglong CsString::ToULongLong(cs_bool *bIsOk) const
{
	return _ToNum<cs_ulonglong>(*this, bIsOk);
}

cs_float CsString::ToFloat(cs_bool *bIsOk) const
{
	return _ToNum<cs_float>(*this, bIsOk);
}

cs_double CsString::ToDouble(cs_bool *bIsOk) const
{
	return _ToNum<cs_double>(*this, bIsOk);
}

cs_decimal CsString::ToDecimal(cs_bool *bIsOk) const
{
	return _ToNum<cs_decimal>(*this, bIsOk);
}
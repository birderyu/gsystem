#include "CsEndian.h"

void CsEndian::ToBigEndianBytes(cs_uint16 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue >> 8);
	nData[1] = (cs_byte)(nValue);
}

void CsEndian::ToBigEndianBytes(cs_uint32 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue >> 24);
	nData[1] = (cs_byte)(nValue >> 16);
	nData[2] = (cs_byte)(nValue >> 8);
	nData[3] = (cs_byte)(nValue);
}

void CsEndian::ToBigEndianBytes(cs_uint64 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue >> 56);
	nData[1] = (cs_byte)(nValue >> 48);
	nData[2] = (cs_byte)(nValue >> 40);
	nData[3] = (cs_byte)(nValue >> 32);
	nData[4] = (cs_byte)(nValue >> 24);
	nData[5] = (cs_byte)(nValue >> 16);
	nData[6] = (cs_byte)(nValue >> 8);
	nData[7] = (cs_byte)(nValue);
}

void CsEndian::ToBigEndianNumber(cs_byte nData[], cs_uint16 &nValue)
{
	nValue = 0;
	nValue += (nData[0] << 8);
	nValue += (nData[1]);
}

void CsEndian::ToBigEndianNumber(cs_byte nData[], cs_uint32 &nValue)
{
	nValue = 0;
	nValue += (nData[0] << 24);
	nValue += (nData[1] << 16);
	nValue += (nData[2] << 8);
	nValue += (nData[3]);
}

void CsEndian::ToBigEndianNumber(cs_byte nData[], cs_uint64 &nValue)
{
	nValue = 0;
	nValue += (nData[0] << 56);
	nValue += (nData[1] << 48);
	nValue += (nData[2] << 40);
	nValue += (nData[3] << 32);
	nValue += (nData[4] << 24);
	nValue += (nData[5] << 16);
	nValue += (nData[6] << 8);
	nValue += (nData[7]);
}

cs_bool CsEndian::Swap(cs_bool val)
{
	return val;
}

cs_char CsEndian::Swap(cs_char val)
{
	return val;
}

cs_schar CsEndian::Swap(cs_schar val)
{
	return val;
}

cs_uchar CsEndian::Swap(cs_uchar val)
{
	return val;
}

cs_short CsEndian::Swap(cs_short val)
{
	return val;
}

cs_ushort CsEndian::Swap(cs_ushort val)
{
	return val;
}

cs_int CsEndian::Swap(cs_int val)
{
	return val;
}

cs_uint CsEndian::Swap(cs_uint val)
{
	return val;
}

cs_long CsEndian::Swap(cs_long val)
{
	return val;
}

cs_ulong CsEndian::Swap(cs_ulong val)
{
	return val;
}

cs_longlong CsEndian::Swap(cs_longlong val)
{
	return val;
}

cs_ulonglong CsEndian::Swap(cs_ulonglong val)
{
	return val;
}

cs_float CsEndian::Swap(cs_float val)
{
	return val;
}

cs_double CsEndian::Swap(cs_double val)
{
	return val;
}

cs_decimal CsEndian::Swap(cs_decimal val)
{
	//cs_uint16 ret = nValue;
	//cs_char *c1 = (cs_char*)&nValue;
	//cs_char *c0 = (cs_char*)&ret;
	//c0[0] = c1[1];
	//c0[1] = c1[0];
	//return ret;
	return val;
}

void CsEndian::ToLittleEndianBytes(cs_uint16 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue);
	nData[1] = (cs_byte)(nValue >> 8);
}

void CsEndian::ToLittleEndianBytes(cs_uint32 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue);
	nData[1] = (cs_byte)(nValue >> 8);
	nData[2] = (cs_byte)(nValue >> 16);
	nData[3] = (cs_byte)(nValue >> 24);
}

void CsEndian::ToLittleEndianBytes(cs_uint64 nValue, cs_byte nData[])
{
	nData[0] = (cs_byte)(nValue);
	nData[1] = (cs_byte)(nValue >> 8);
	nData[2] = (cs_byte)(nValue >> 16);
	nData[3] = (cs_byte)(nValue >> 24); 
	nData[4] = (cs_byte)(nValue >> 32);
	nData[5] = (cs_byte)(nValue >> 40);
	nData[6] = (cs_byte)(nValue >> 48);
	nData[7] = (cs_byte)(nValue >> 56);
}

void CsEndian::ToLittleEndianNumber(cs_byte nData[], cs_uint16 &nValue)
{
	nValue = 0;
	nValue += (nData[0]);
	nValue += (nData[1] << 8);
}

void CsEndian::ToLittleEndianNumber(cs_byte nData[], cs_uint32 &nValue)
{
	nValue = 0;
	nValue += (nData[0]);
	nValue += (nData[1] << 8);
	nValue += (nData[2] << 16);
	nValue += (nData[3] << 24);
}

void CsEndian::ToLittleEndianNumber(cs_byte nData[], cs_uint64 &nValue)
{
	nValue = 0;
	nValue += (nData[0]);
	nValue += (nData[1] << 8);
	nValue += (nData[2] << 16);
	nValue += (nData[3] << 24);
	nValue += (nData[4] << 32);
	nValue += (nData[5] << 40);
	nValue += (nData[6] << 48);
	nValue += (nData[7] << 56);
}

CsEndian::CsEndian()
{

}

CsEndian::CsEndian(const CsEndian&)
{

}

CsEndian::~CsEndian()
{

}
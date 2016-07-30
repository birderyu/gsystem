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

CsEndian::~CsEndian()
{

}
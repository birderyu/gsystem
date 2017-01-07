#include "gendian.h"

void GEndian::ToBigEndianBytes(guint16 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue >> 8);
	nData[1] = (gbyte)(nValue);
}

void GEndian::ToBigEndianBytes(guint32 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue >> 24);
	nData[1] = (gbyte)(nValue >> 16);
	nData[2] = (gbyte)(nValue >> 8);
	nData[3] = (gbyte)(nValue);
}

void GEndian::ToBigEndianBytes(guint64 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue >> 56);
	nData[1] = (gbyte)(nValue >> 48);
	nData[2] = (gbyte)(nValue >> 40);
	nData[3] = (gbyte)(nValue >> 32);
	nData[4] = (gbyte)(nValue >> 24);
	nData[5] = (gbyte)(nValue >> 16);
	nData[6] = (gbyte)(nValue >> 8);
	nData[7] = (gbyte)(nValue);
}

void GEndian::ToBigEndianNumber(gbyte nData[], guint16 &nValue)
{
	nValue = 0;
	nValue += (nData[0] << 8);
	nValue += (nData[1]);
}

void GEndian::ToBigEndianNumber(gbyte nData[], guint32 &nValue)
{
	nValue = 0;
	nValue += (nData[0] << 24);
	nValue += (nData[1] << 16);
	nValue += (nData[2] << 8);
	nValue += (nData[3]);
}

void GEndian::ToBigEndianNumber(gbyte nData[], guint64 &nValue)
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

gbool GEndian::Swap(gbool val)
{
	return val;
}

gchar GEndian::Swap(gchar val)
{
	return val;
}

gschar GEndian::Swap(gschar val)
{
	return val;
}

guchar GEndian::Swap(guchar val)
{
	return val;
}

gshort GEndian::Swap(gshort val)
{
	return val;
}

gushort GEndian::Swap(gushort val)
{
	return val;
}

gint GEndian::Swap(gint val)
{
	return val;
}

guint GEndian::Swap(guint val)
{
	return val;
}

glong GEndian::Swap(glong val)
{
	return val;
}

gulong GEndian::Swap(gulong val)
{
	return val;
}

glonglong GEndian::Swap(glonglong val)
{
	return val;
}

gulonglong GEndian::Swap(gulonglong val)
{
	return val;
}

gfloat GEndian::Swap(gfloat val)
{
	return val;
}

gdouble GEndian::Swap(gdouble val)
{
	return val;
}

gdecimal GEndian::Swap(gdecimal val)
{
	return val;
}

void GEndian::ToLittleEndianBytes(guint16 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue);
	nData[1] = (gbyte)(nValue >> 8);
}

void GEndian::ToLittleEndianBytes(guint32 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue);
	nData[1] = (gbyte)(nValue >> 8);
	nData[2] = (gbyte)(nValue >> 16);
	nData[3] = (gbyte)(nValue >> 24);
}

void GEndian::ToLittleEndianBytes(guint64 nValue, gbyte nData[])
{
	nData[0] = (gbyte)(nValue);
	nData[1] = (gbyte)(nValue >> 8);
	nData[2] = (gbyte)(nValue >> 16);
	nData[3] = (gbyte)(nValue >> 24); 
	nData[4] = (gbyte)(nValue >> 32);
	nData[5] = (gbyte)(nValue >> 40);
	nData[6] = (gbyte)(nValue >> 48);
	nData[7] = (gbyte)(nValue >> 56);
}

void GEndian::ToLittleEndianNumber(gbyte nData[], guint16 &nValue)
{
	nValue = 0;
	nValue += (nData[0]);
	nValue += (nData[1] << 8);
}

void GEndian::ToLittleEndianNumber(gbyte nData[], guint32 &nValue)
{
	nValue = 0;
	nValue += (nData[0]);
	nValue += (nData[1] << 8);
	nValue += (nData[2] << 16);
	nValue += (nData[3] << 24);
}

void GEndian::ToLittleEndianNumber(gbyte nData[], guint64 &nValue)
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

GEndian::GEndian()
{

}

GEndian::GEndian(const GEndian&)
{

}

GEndian::~GEndian()
{

}
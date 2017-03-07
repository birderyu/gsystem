#include "gendian.h"

void GEndian::ToBigEndianBytes(guint16 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val >> 8);
	bytes[1] = (gbyte)(val);
}

void GEndian::ToBigEndianBytes(guint32 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val >> 24);
	bytes[1] = (gbyte)(val >> 16);
	bytes[2] = (gbyte)(val >> 8);
	bytes[3] = (gbyte)(val);
}

void GEndian::ToBigEndianBytes(guint64 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val >> 56);
	bytes[1] = (gbyte)(val >> 48);
	bytes[2] = (gbyte)(val >> 40);
	bytes[3] = (gbyte)(val >> 32);
	bytes[4] = (gbyte)(val >> 24);
	bytes[5] = (gbyte)(val >> 16);
	bytes[6] = (gbyte)(val >> 8);
	bytes[7] = (gbyte)(val);
}

void GEndian::ToBigEndianNumber(gbyte bytes[], guint16 &val)
{
	val = 0;
	val += (bytes[0] << 8);
	val += (bytes[1]);
}

void GEndian::ToBigEndianNumber(gbyte bytes[], guint32 &val)
{
	val = 0;
	val += (bytes[0] << 24);
	val += (bytes[1] << 16);
	val += (bytes[2] << 8);
	val += (bytes[3]);
}

void GEndian::ToBigEndianNumber(gbyte bytes[], guint64 &val)
{
	val = 0;
	val += (bytes[0] << 56);
	val += (bytes[1] << 48);
	val += (bytes[2] << 40);
	val += (bytes[3] << 32);
	val += (bytes[4] << 24);
	val += (bytes[5] << 16);
	val += (bytes[6] << 8);
	val += (bytes[7]);
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

void GEndian::ToLittleEndianBytes(guint16 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val);
	bytes[1] = (gbyte)(val >> 8);
}

void GEndian::ToLittleEndianBytes(guint32 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val);
	bytes[1] = (gbyte)(val >> 8);
	bytes[2] = (gbyte)(val >> 16);
	bytes[3] = (gbyte)(val >> 24);
}

void GEndian::ToLittleEndianBytes(guint64 val, gbyte bytes[])
{
	bytes[0] = (gbyte)(val);
	bytes[1] = (gbyte)(val >> 8);
	bytes[2] = (gbyte)(val >> 16);
	bytes[3] = (gbyte)(val >> 24); 
	bytes[4] = (gbyte)(val >> 32);
	bytes[5] = (gbyte)(val >> 40);
	bytes[6] = (gbyte)(val >> 48);
	bytes[7] = (gbyte)(val >> 56);
}

void GEndian::ToLittleEndianNumber(gbyte bytes[], guint16 &val)
{
	val = 0;
	val += (bytes[0]);
	val += (bytes[1] << 8);
}

void GEndian::ToLittleEndianNumber(gbyte bytes[], guint32 &val)
{
	val = 0;
	val += (bytes[0]);
	val += (bytes[1] << 8);
	val += (bytes[2] << 16);
	val += (bytes[3] << 24);
}

void GEndian::ToLittleEndianNumber(gbyte bytes[], guint64 &val)
{
	val = 0;
	val += (bytes[0]);
	val += (bytes[1] << 8);
	val += (bytes[2] << 16);
	val += (bytes[3] << 24);
	val += (bytes[4] << 32);
	val += (bytes[5] << 40);
	val += (bytes[6] << 48);
	val += (bytes[7] << 56);
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
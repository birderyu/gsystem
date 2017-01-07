#include "gstring.h"
#include <sstream>

template <typename T>
GString _FromNum(T nNum, gint nBase)
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
	return GString(oss.str().c_str());
}

template <typename T>
T _ToNum(const GString &str, gbool *isok)
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

GString GString::FromNum(gsmall nNum, gint nBase)
{
	return _FromNum<gsmall>(nNum, nBase);
}

GString GString::FromNum(gusmall nNum, gint nBase)
{
	return _FromNum<gusmall>(nNum, nBase);
}

GString GString::FromNum(gshort nNum, gint nBase)
{
	return _FromNum<gshort>(nNum, nBase);
}

GString GString::FromNum(gushort nNum, gint nBase)
{
	return _FromNum<gushort>(nNum, nBase);
}

GString GString::FromNum(gint nNum, gint nBase)
{
	return _FromNum<gint>(nNum, nBase);
}

GString GString::FromNum(guint nNum, gint nBase)
{
	return _FromNum<guint>(nNum, nBase);
}

GString GString::FromNum(glong nNum, gint nBase)
{
	return _FromNum<glong>(nNum, nBase);
}

GString GString::FromNum(gulong nNum, gint nBase)
{
	return _FromNum<gulong>(nNum, nBase);
}

GString GString::FromNum(glonglong nNum, gint nBase)
{
	return _FromNum<glonglong>(nNum, nBase);
}

GString GString::FromNum(gulonglong nNum, gint nBase)
{
	return _FromNum<gulonglong>(nNum, nBase);
}

GString GString::FromNum(gfloat nNum, gint nBase)
{
	return _FromNum<gfloat>(nNum, nBase);
}

GString GString::FromNum(gdouble nNum, gint nBase)
{
	return _FromNum<gdouble>(nNum, nBase);
}

GString GString::FromNum(gdecimal nNum, gint nBase)
{
	return _FromNum<gdecimal>(nNum, nBase);
}

gsmall GString::ToSmall(gbool *bIsOk) const
{
	return _ToNum<gsmall>(*this, bIsOk);
}

gusmall GString::ToUSmall(gbool *bIsOk) const
{
	return _ToNum<gusmall>(*this, bIsOk);
}

gshort GString::ToShort(gbool *bIsOk) const
{
	return _ToNum<gshort>(*this, bIsOk);
}

gushort GString::ToUShort(gbool *bIsOk) const
{
	return _ToNum<gushort>(*this, bIsOk);
}

gint GString::ToInt(gbool *bIsOk) const
{
	return _ToNum<gint>(*this, bIsOk);
}

guint GString::ToUInt(gbool *bIsOk) const
{
	return _ToNum<guint>(*this, bIsOk);
}

glong GString::ToLong(gbool *bIsOk) const
{
	return _ToNum<glong>(*this, bIsOk);
}

gulong GString::ToULong(gbool *bIsOk) const
{
	return _ToNum<gulong>(*this, bIsOk);
}

glonglong GString::ToLongLong(gbool *bIsOk) const
{
	return _ToNum<glonglong>(*this, bIsOk);
}

gulonglong GString::ToULongLong(gbool *bIsOk) const
{
	return _ToNum<gulonglong>(*this, bIsOk);
}

gfloat GString::ToFloat(gbool *bIsOk) const
{
	return _ToNum<gfloat>(*this, bIsOk);
}

gdouble GString::ToDouble(gbool *bIsOk) const
{
	return _ToNum<gdouble>(*this, bIsOk);
}

gdecimal GString::ToDecimal(gbool *bIsOk) const
{
	return _ToNum<gdecimal>(*this, bIsOk);
}
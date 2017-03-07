#include "gstring.h"
#include "gcstringhelper.h"

namespace GNova {
	namespace String {
		namespace Private {

			template <typename T>
			GString NumberToString(T nNum, gint nBase)
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

		}
	}
}

GString GString::Number(gsmall nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gsmall>(nNum, nBase);
}

GString GString::Number(gusmall nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gusmall>(nNum, nBase);
}

GString GString::Number(gshort nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gshort>(nNum, nBase);
}

GString GString::Number(gushort nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gushort>(nNum, nBase);
}

GString GString::Number(gint nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gint>(nNum, nBase);
}

GString GString::Number(guint nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<guint>(nNum, nBase);
}

GString GString::Number(glong nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<glong>(nNum, nBase);
}

GString GString::Number(gulong nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gulong>(nNum, nBase);
}

GString GString::Number(glonglong nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<glonglong>(nNum, nBase);
}

GString GString::Number(gulonglong nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gulonglong>(nNum, nBase);
}

GString GString::Number(gfloat nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gfloat>(nNum, nBase);
}

GString GString::Number(gdouble nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gdouble>(nNum, nBase);
}

GString GString::Number(gdecimal nNum, gint nBase)
{
	return GNova::String::Private::NumberToString<gdecimal>(nNum, nBase);
}

gsmall GString::ToSmall(gbool *ok) const
{
	return GCStringHelper::ToNum<gsmall>(CString(), ok);
}

gusmall GString::ToUSmall(gbool *ok) const
{
	return GCStringHelper::ToNum<gusmall>(CString(), ok);
}

gshort GString::ToShort(gbool *ok) const
{
	return GCStringHelper::ToNum<gshort>(CString(), ok);
}

gushort GString::ToUShort(gbool *ok) const
{
	return GCStringHelper::ToNum<gushort>(CString(), ok);
}

gint GString::ToInt(gbool *ok) const
{
	return GCStringHelper::ToNum<gint>(CString(), ok);
}

guint GString::ToUInt(gbool *ok) const
{
	return GCStringHelper::ToNum<guint>(CString(), ok);
}

glong GString::ToLong(gbool *ok) const
{
	return GCStringHelper::ToNum<glong>(CString(), ok);
}

gulong GString::ToULong(gbool *ok) const
{
	return GCStringHelper::ToNum<gulong>(CString(), ok);
}

glonglong GString::ToLongLong(gbool *ok) const
{
	return GCStringHelper::ToNum<glonglong>(CString(), ok);
}

gulonglong GString::ToULongLong(gbool *ok) const
{
	return GCStringHelper::ToNum<gulonglong>(CString(), ok);
}

gfloat GString::ToFloat(gbool *ok) const
{
	return GCStringHelper::ToNum<gfloat>(CString(), ok);
}

gdouble GString::ToDouble(gbool *ok) const
{
	return GCStringHelper::ToNum<gdouble>(CString(), ok);
}

glongdouble GString::ToLongDouble(gbool *ok) const
{
	return GCStringHelper::ToNum<glongdouble>(CString(), ok);
}
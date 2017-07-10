#ifndef _CORE_STRING_16_BIT_H_
#define _CORE_STRING_16_BIT_H_

#include "gseries.h"
#include "gserializable.h"

namespace gsystem { // gsystem
	class GVariety;
} // namespace gsystem

namespace gsystem { // gsystem

// 以16位字符为单元的字符串
class GAPI GString16 final
	: public GArray<gchar16>
	, public GSerializable
{
	friend class GVariety;
	friend GAPI GString16 operator+(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator==(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator!=(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator>(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator>=(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator<(const GString16 &s1, const GString16 &s2);
	friend GAPI gbool operator<=(const GString16 &s1, const GString16 &s2);

public: // 静态方法
	static GString16 Number(gsmall num, gint base = 10);
	static GString16 Number(gusmall num, gint base = 10);
	static GString16 Number(gshort num, gint base = 10);
	static GString16 Number(gushort num, gint base = 10);
	static GString16 Number(gint num, gint base = 10);
	static GString16 Number(guint num, gint base = 10);
	static GString16 Number(glong num, gint base = 10);
	static GString16 Number(gulong num, gint base = 10);
	static GString16 Number(glonglong num, gint base = 10);
	static GString16 Number(gulonglong num, gint base = 10);
	static GString16 Number(gfloat num, gint base = 10);
	static GString16 Number(gdouble num, gint base = 10);
	static GString16 Number(glongdouble num, gint base = 10);


};

}

#endif // _CORE_STRING_8_BIT_H_
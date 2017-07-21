//  ‰»Î¡˜
#ifndef _CORE_INPUT_STREAM_H_
#define _CORE_INPUT_STREAM_H_

#include "gstream.h"

class GAPI GInputStream
	: virtual public GStream
{
public:
	virtual ~GInputStream() = 0;
	gbool IsInput() const;

	virtual GInputStream &operator<<(gbool) = 0;
	virtual GInputStream &operator<<(gchar) = 0;
	virtual GInputStream &operator<<(gschar) = 0;
	virtual GInputStream &operator<<(guchar) = 0;
	virtual GInputStream &operator<<(gwchar) = 0;
	virtual GInputStream &operator<<(gshort) = 0;
	virtual GInputStream &operator<<(gushort) = 0;
	virtual GInputStream &operator<<(gint) = 0;
	virtual GInputStream &operator<<(guint) = 0;
	virtual GInputStream &operator<<(glong) = 0;
	virtual GInputStream &operator<<(gulong) = 0;
	virtual GInputStream &operator<<(glonglong) = 0;
	virtual GInputStream &operator<<(gulonglong) = 0;
	virtual GInputStream &operator<<(gfloat) = 0;
	virtual GInputStream &operator<<(gdouble) = 0;
	virtual GInputStream &operator<<(gdecimal) = 0;
};

#endif // _CORE_INPUT_STREAM_H_
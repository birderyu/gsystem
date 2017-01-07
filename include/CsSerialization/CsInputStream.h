//  ‰»Î¡˜
#ifndef _CORE_INPUT_STREAM_H_
#define _CORE_INPUT_STREAM_H_

#include "CsStream.h"

class GAPI CsInputStream
	: virtual public CsStream
{
public:
	virtual ~CsInputStream() = 0;
	gbool IsInput() const;

	virtual CsInputStream &operator<<(gbool) = 0;
	virtual CsInputStream &operator<<(gchar) = 0;
	virtual CsInputStream &operator<<(gschar) = 0;
	virtual CsInputStream &operator<<(guchar) = 0;
	virtual CsInputStream &operator<<(gwchar) = 0;
	virtual CsInputStream &operator<<(gshort) = 0;
	virtual CsInputStream &operator<<(gushort) = 0;
	virtual CsInputStream &operator<<(gint) = 0;
	virtual CsInputStream &operator<<(guint) = 0;
	virtual CsInputStream &operator<<(glong) = 0;
	virtual CsInputStream &operator<<(gulong) = 0;
	virtual CsInputStream &operator<<(glonglong) = 0;
	virtual CsInputStream &operator<<(gulonglong) = 0;
	virtual CsInputStream &operator<<(gfloat) = 0;
	virtual CsInputStream &operator<<(gdouble) = 0;
	virtual CsInputStream &operator<<(gdecimal) = 0;
};

#endif // _CORE_INPUT_STREAM_H_
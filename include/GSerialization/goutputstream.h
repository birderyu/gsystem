// Êä³öÁ÷
#ifndef _CORE_OUTPUT_STREAM_H_
#define _CORE_OUTPUT_STREAM_H_

#include "gstream.h"

class GAPI GOutputStream
	: virtual public GStream
{
public:
	virtual ~GOutputStream() = 0;
	gbool IsOutput() const;

	virtual GOutputStream &operator>>(gbool &) = 0;
	virtual GOutputStream &operator>>(gchar &) = 0;
	virtual GOutputStream &operator>>(gschar &) = 0;
	virtual GOutputStream &operator>>(guchar &) = 0;
	virtual GOutputStream &operator>>(gwchar &) = 0;
	virtual GOutputStream &operator>>(gshort &) = 0;
	virtual GOutputStream &operator>>(gushort &) = 0;
	virtual GOutputStream &operator>>(gint &) = 0;
	virtual GOutputStream &operator>>(guint &) = 0;
	virtual GOutputStream &operator>>(glong &) = 0;
	virtual GOutputStream &operator>>(gulong &) = 0;
	virtual GOutputStream &operator>>(glonglong &) = 0;
	virtual GOutputStream &operator>>(gulonglong &) = 0;
	virtual GOutputStream &operator>>(gfloat &) = 0;
	virtual GOutputStream &operator>>(gdouble &) = 0;
	virtual GOutputStream &operator>>(gdecimal &) = 0;
};

#endif // _CORE_OUTPUT_STREAM_H_
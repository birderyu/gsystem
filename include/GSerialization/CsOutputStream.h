// Êä³öÁ÷
#ifndef _CORE_OUTPUT_STREAM_H_
#define _CORE_OUTPUT_STREAM_H_

#include "CsStream.h"

class GAPI CsOutputStream
	: virtual public CsStream
{
public:
	virtual ~CsOutputStream() = 0;
	gbool IsOutput() const;

	virtual CsOutputStream &operator>>(gbool &) = 0;
	virtual CsOutputStream &operator>>(gchar &) = 0;
	virtual CsOutputStream &operator>>(gschar &) = 0;
	virtual CsOutputStream &operator>>(guchar &) = 0;
	virtual CsOutputStream &operator>>(gwchar &) = 0;
	virtual CsOutputStream &operator>>(gshort &) = 0;
	virtual CsOutputStream &operator>>(gushort &) = 0;
	virtual CsOutputStream &operator>>(gint &) = 0;
	virtual CsOutputStream &operator>>(guint &) = 0;
	virtual CsOutputStream &operator>>(glong &) = 0;
	virtual CsOutputStream &operator>>(gulong &) = 0;
	virtual CsOutputStream &operator>>(glonglong &) = 0;
	virtual CsOutputStream &operator>>(gulonglong &) = 0;
	virtual CsOutputStream &operator>>(gfloat &) = 0;
	virtual CsOutputStream &operator>>(gdouble &) = 0;
	virtual CsOutputStream &operator>>(gdecimal &) = 0;
};

#endif // _CORE_OUTPUT_STREAM_H_
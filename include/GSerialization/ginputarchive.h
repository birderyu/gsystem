#ifndef _CORE_INPUT_ARCHIVE_H_
#define _CORE_INPUT_ARCHIVE_H_

#include "garchive.h"

class GAPI GInputArchive
	: public GArchive
{
public:
	GInputArchive(GStream &);
	virtual ~GInputArchive();

public:
	GArchive &operator>>(gbool &);
	GArchive &operator>>(gchar &);
	GArchive &operator>>(gschar &);
	GArchive &operator>>(guchar &);
	GArchive &operator>>(gwchar &);
	GArchive &operator>>(gshort &);
	GArchive &operator>>(gushort &);
	GArchive &operator>>(gint &);
	GArchive &operator>>(guint &);
	GArchive &operator>>(glong &);
	GArchive &operator>>(gulong &);
	GArchive &operator>>(glonglong &);
	GArchive &operator>>(gulonglong &);
	GArchive &operator>>(gfloat &);
	GArchive &operator>>(gdouble &);
	GArchive &operator>>(gdecimal &);
};

#endif // _CORE_INPUT_ARCHIVE_H_
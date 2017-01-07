#ifndef _CORE_INPUT_ARCHIVE_H_
#define _CORE_INPUT_ARCHIVE_H_

#include "CsArchive.h"

class GAPI CsInputArchive
	: public CsArchive
{
public:
	CsInputArchive(GFile &);
	virtual ~CsInputArchive();

public:
	CsArchive &operator>>(gbool &);
	CsArchive &operator>>(gchar &);
	CsArchive &operator>>(gschar &);
	CsArchive &operator>>(guchar &);
	CsArchive &operator>>(gwchar &);
	CsArchive &operator>>(gshort &);
	CsArchive &operator>>(gushort &);
	CsArchive &operator>>(gint &);
	CsArchive &operator>>(guint &);
	CsArchive &operator>>(glong &);
	CsArchive &operator>>(gulong &);
	CsArchive &operator>>(glonglong &);
	CsArchive &operator>>(gulonglong &);
	CsArchive &operator>>(gfloat &);
	CsArchive &operator>>(gdouble &);
	CsArchive &operator>>(gdecimal &);
};

CsArchive::TYPE CsInputArchive::Type()
{
	return CsArchive::ARCHIVE_TYPE_INPUT;
}

CsArchive &CsInputArchive::operator>>(gbool &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gchar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gschar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(guchar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gwchar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gshort &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gushort &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gint &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(guint &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(glong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gulong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(glonglong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gulonglong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gfloat &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gdouble &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(gdecimal &)
{
	return *this;
}

#endif // _CORE_INPUT_ARCHIVE_H_
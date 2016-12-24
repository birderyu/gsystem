#ifndef _CORE_INPUT_ARCHIVE_H_
#define _CORE_INPUT_ARCHIVE_H_

#include "CsArchive.h"

class CS_API CsInputArchive
	: public CsArchive
{
public:
	CsInputArchive(CsFile &);
	virtual ~CsInputArchive();

public:
	CsArchive &operator>>(cs_bool &);
	CsArchive &operator>>(cs_char &);
	CsArchive &operator>>(cs_schar &);
	CsArchive &operator>>(cs_uchar &);
	CsArchive &operator>>(cs_wchar &);
	CsArchive &operator>>(cs_short &);
	CsArchive &operator>>(cs_ushort &);
	CsArchive &operator>>(cs_int &);
	CsArchive &operator>>(cs_uint &);
	CsArchive &operator>>(cs_long &);
	CsArchive &operator>>(cs_ulong &);
	CsArchive &operator>>(cs_longlong &);
	CsArchive &operator>>(cs_ulonglong &);
	CsArchive &operator>>(cs_float &);
	CsArchive &operator>>(cs_double &);
	CsArchive &operator>>(cs_decimal &);
};

CsArchive::TYPE CsInputArchive::Type()
{
	return CsArchive::ARCHIVE_TYPE_INPUT;
}

CsArchive &CsInputArchive::operator>>(cs_bool &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_char &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_schar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_uchar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_wchar &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_short &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_ushort &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_int &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_uint &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_long &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_ulong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_longlong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_ulonglong &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_float &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_double &)
{
	return *this;
}

CsArchive &CsInputArchive::operator>>(cs_decimal &)
{
	return *this;
}

#endif // _CORE_INPUT_ARCHIVE_H_
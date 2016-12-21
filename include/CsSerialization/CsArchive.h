#ifndef _CORE_ARCHIVE_H_
#define _CORE_ARCHIVE_H_

#include "CsGlobal.h"

class CsFile;

class CS_API CsArchive
{
public:
	// 根据文件创建一个档案
	CsArchive(CsFile &);
	virtual ~CsArchive();

	virtual cs_bool Input() = 0;
	virtual cs_bool Output() = 0;

	virtual cs_void Flush() = 0;
	virtual cs_void Close() = 0;
	virtual cs_void Abort() = 0;

	virtual cs_void PushCode(cs_uint) = 0;
	virtual cs_uint PopCode() = 0;

	virtual CsArchive &operator<<(cs_bool) = 0;
	virtual CsArchive &operator<<(cs_char) = 0;
	virtual CsArchive &operator<<(cs_schar) = 0;
	virtual CsArchive &operator<<(cs_uchar) = 0;
	virtual CsArchive &operator<<(cs_wchar) = 0;
	virtual CsArchive &operator<<(cs_short) = 0;
	virtual CsArchive &operator<<(cs_ushort) = 0;
	virtual CsArchive &operator<<(cs_int) = 0;
	virtual CsArchive &operator<<(cs_uint) = 0;
	virtual CsArchive &operator<<(cs_long) = 0;
	virtual CsArchive &operator<<(cs_ulong) = 0;
	virtual CsArchive &operator<<(cs_longlong) = 0;
	virtual CsArchive &operator<<(cs_ulonglong) = 0;
	virtual CsArchive &operator<<(cs_float) = 0;
	virtual CsArchive &operator<<(cs_double) = 0;
	virtual CsArchive &operator<<(cs_decimal) = 0;

	virtual CsArchive &operator>>(cs_bool &) = 0;
	virtual CsArchive &operator>>(cs_char &) = 0;
	virtual CsArchive &operator>>(cs_schar &) = 0;
	virtual CsArchive &operator>>(cs_uchar &) = 0;
	virtual CsArchive &operator>>(cs_wchar &) = 0;
	virtual CsArchive &operator>>(cs_short &) = 0;
	virtual CsArchive &operator>>(cs_ushort &) = 0;
	virtual CsArchive &operator>>(cs_int &) = 0;
	virtual CsArchive &operator>>(cs_uint &) = 0;
	virtual CsArchive &operator>>(cs_long &) = 0;
	virtual CsArchive &operator>>(cs_ulong &) = 0;
	virtual CsArchive &operator>>(cs_longlong &) = 0;
	virtual CsArchive &operator>>(cs_ulonglong &) = 0;
	virtual CsArchive &operator>>(cs_float &) = 0;
	virtual CsArchive &operator>>(cs_double &) = 0;
	virtual CsArchive &operator>>(cs_decimal &) = 0;

private:
	CsArchive(const CsArchive &);
	CsArchive &operator=(const CsArchive &);

protected:
	CsFile &m_rFile;
};

inline CsArchive::CsArchive(CsFile &file)
: m_rFile(file)
{

}

inline CsArchive::CsArchive(const CsArchive &archive)
: m_rFile(archive.m_rFile)
{

}

inline CsArchive::~CsArchive()
{

}

inline CsArchive &CsArchive::operator=(const CsArchive &)
{
	return *this;
}

#endif // _CORE_ARCHIVE_H_
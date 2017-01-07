#ifndef _SERIALIZATION_ARCHIVE_H_
#define _SERIALIZATION_ARCHIVE_H_

#include "gglobal.h"

class CsStream;

class GAPI CsArchive
{
public:
	// 根据流创建一个档案
	CsArchive(CsStream &);
	virtual ~CsArchive();

	virtual gbool Input() const = 0;
	virtual gbool Output() const = 0;

	// 二进制 or 文本
	virtual gbool IsBinary() const = 0;

	// 将缓冲区中的文件放入
	virtual gvoid Flush() = 0;
	virtual gvoid Close() = 0;
	virtual gvoid Abort() = 0;

	virtual gvoid PushCode(guint) = 0;
	virtual guint PopCode() = 0;

	virtual CsArchive &operator<<(gbool) = 0;
	virtual CsArchive &operator<<(gchar) = 0;
	virtual CsArchive &operator<<(gschar) = 0;
	virtual CsArchive &operator<<(guchar) = 0;
	virtual CsArchive &operator<<(gwchar) = 0;
	virtual CsArchive &operator<<(gshort) = 0;
	virtual CsArchive &operator<<(gushort) = 0;
	virtual CsArchive &operator<<(gint) = 0;
	virtual CsArchive &operator<<(guint) = 0;
	virtual CsArchive &operator<<(glong) = 0;
	virtual CsArchive &operator<<(gulong) = 0;
	virtual CsArchive &operator<<(glonglong) = 0;
	virtual CsArchive &operator<<(gulonglong) = 0;
	virtual CsArchive &operator<<(gfloat) = 0;
	virtual CsArchive &operator<<(gdouble) = 0;
	virtual CsArchive &operator<<(gdecimal) = 0;

	virtual CsArchive &operator>>(gbool &) = 0;
	virtual CsArchive &operator>>(gchar &) = 0;
	virtual CsArchive &operator>>(gschar &) = 0;
	virtual CsArchive &operator>>(guchar &) = 0;
	virtual CsArchive &operator>>(gwchar &) = 0;
	virtual CsArchive &operator>>(gshort &) = 0;
	virtual CsArchive &operator>>(gushort &) = 0;
	virtual CsArchive &operator>>(gint &) = 0;
	virtual CsArchive &operator>>(guint &) = 0;
	virtual CsArchive &operator>>(glong &) = 0;
	virtual CsArchive &operator>>(gulong &) = 0;
	virtual CsArchive &operator>>(glonglong &) = 0;
	virtual CsArchive &operator>>(gulonglong &) = 0;
	virtual CsArchive &operator>>(gfloat &) = 0;
	virtual CsArchive &operator>>(gdouble &) = 0;
	virtual CsArchive &operator>>(gdecimal &) = 0;

private:
	CsArchive(const CsArchive &);
	CsArchive &operator=(const CsArchive &);

protected:
	CsStream &m_rStream;
};

inline CsArchive::CsArchive(CsStream &stream)
: m_rStream(stream)
{

}

inline CsArchive::CsArchive(const CsArchive &archive)
: m_rStream(archive.m_rStream)
{

}

inline CsArchive::~CsArchive()
{

}

inline CsArchive &CsArchive::operator=(const CsArchive &)
{
	return *this;
}

#endif // _SERIALIZATION_ARCHIVE_H_
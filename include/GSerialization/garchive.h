#ifndef _SERIALIZATION_ARCHIVE_H_
#define _SERIALIZATION_ARCHIVE_H_

#include "GCore/gglobal.h"

class GStream;

class GAPI GArchive
{
public:
	// 根据流创建一个档案
	GArchive(GStream &);
	virtual ~GArchive();

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

	virtual GArchive &operator<<(gbool) = 0;
	virtual GArchive &operator<<(gchar) = 0;
	virtual GArchive &operator<<(gschar) = 0;
	virtual GArchive &operator<<(guchar) = 0;
	virtual GArchive &operator<<(gwchar) = 0;
	virtual GArchive &operator<<(gshort) = 0;
	virtual GArchive &operator<<(gushort) = 0;
	virtual GArchive &operator<<(gint) = 0;
	virtual GArchive &operator<<(guint) = 0;
	virtual GArchive &operator<<(glong) = 0;
	virtual GArchive &operator<<(gulong) = 0;
	virtual GArchive &operator<<(glonglong) = 0;
	virtual GArchive &operator<<(gulonglong) = 0;
	virtual GArchive &operator<<(gfloat) = 0;
	virtual GArchive &operator<<(gdouble) = 0;
	virtual GArchive &operator<<(gdecimal) = 0;

	virtual GArchive &operator>>(gbool &) = 0;
	virtual GArchive &operator>>(gchar &) = 0;
	virtual GArchive &operator>>(gschar &) = 0;
	virtual GArchive &operator>>(guchar &) = 0;
	virtual GArchive &operator>>(gwchar &) = 0;
	virtual GArchive &operator>>(gshort &) = 0;
	virtual GArchive &operator>>(gushort &) = 0;
	virtual GArchive &operator>>(gint &) = 0;
	virtual GArchive &operator>>(guint &) = 0;
	virtual GArchive &operator>>(glong &) = 0;
	virtual GArchive &operator>>(gulong &) = 0;
	virtual GArchive &operator>>(glonglong &) = 0;
	virtual GArchive &operator>>(gulonglong &) = 0;
	virtual GArchive &operator>>(gfloat &) = 0;
	virtual GArchive &operator>>(gdouble &) = 0;
	virtual GArchive &operator>>(gdecimal &) = 0;

private:
	GArchive(const GArchive &);
	GArchive &operator=(const GArchive &);

protected:
	GStream &m_rStream;
};

inline GArchive::GArchive(GStream &stream)
: m_rStream(stream)
{

}

inline GArchive::GArchive(const GArchive &archive)
: m_rStream(archive.m_rStream)
{

}

inline GArchive::~GArchive()
{

}

inline GArchive &GArchive::operator=(const GArchive &)
{
	return *this;
}

#endif // _SERIALIZATION_ARCHIVE_H_
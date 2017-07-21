#ifndef _SERIALIZATION_ARCHIVE_H_
#define _SERIALIZATION_ARCHIVE_H_

#include "GCore/gglobal.h"

namespace gsystem {
	namespace stream {
		class GStream;
	}
}

namespace gsystem {
namespace archive {

class GAPI GBaseArchive
{
public:
	// 根据流创建一个档案
	GBaseArchive(stream::GStream &);
	virtual ~GBaseArchive();

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

	virtual GBaseArchive &operator<<(gbool) = 0;
	virtual GBaseArchive &operator<<(gchar) = 0;
	virtual GBaseArchive &operator<<(gschar) = 0;
	virtual GBaseArchive &operator<<(guchar) = 0;
	virtual GBaseArchive &operator<<(gwchar) = 0;
	virtual GBaseArchive &operator<<(gshort) = 0;
	virtual GBaseArchive &operator<<(gushort) = 0;
	virtual GBaseArchive &operator<<(gint) = 0;
	virtual GBaseArchive &operator<<(guint) = 0;
	virtual GBaseArchive &operator<<(glong) = 0;
	virtual GBaseArchive &operator<<(gulong) = 0;
	virtual GBaseArchive &operator<<(glonglong) = 0;
	virtual GBaseArchive &operator<<(gulonglong) = 0;
	virtual GBaseArchive &operator<<(gfloat) = 0;
	virtual GBaseArchive &operator<<(gdouble) = 0;
	virtual GBaseArchive &operator<<(gdecimal) = 0;

	virtual GBaseArchive &operator>>(gbool &) = 0;
	virtual GBaseArchive &operator>>(gchar &) = 0;
	virtual GBaseArchive &operator>>(gschar &) = 0;
	virtual GBaseArchive &operator>>(guchar &) = 0;
	virtual GBaseArchive &operator>>(gwchar &) = 0;
	virtual GBaseArchive &operator>>(gshort &) = 0;
	virtual GBaseArchive &operator>>(gushort &) = 0;
	virtual GBaseArchive &operator>>(gint &) = 0;
	virtual GBaseArchive &operator>>(guint &) = 0;
	virtual GBaseArchive &operator>>(glong &) = 0;
	virtual GBaseArchive &operator>>(gulong &) = 0;
	virtual GBaseArchive &operator>>(glonglong &) = 0;
	virtual GBaseArchive &operator>>(gulonglong &) = 0;
	virtual GBaseArchive &operator>>(gfloat &) = 0;
	virtual GBaseArchive &operator>>(gdouble &) = 0;
	virtual GBaseArchive &operator>>(gdecimal &) = 0;

private:
	GBaseArchive(const GBaseArchive &);
	GBaseArchive &operator=(const GBaseArchive &);

protected:
	stream::GStream &m_rStream;
};

GINLINE GArchive::GArchive(stream::GStream &stream)
: m_rStream(stream)
{

}

GINLINE GArchive::GArchive(const GArchive &archive)
: m_rStream(archive.m_rStream)
{

}

GINLINE GArchive::~GArchive()
{

}

GINLINE GArchive &GArchive::operator=(const GArchive &)
{
	return *this;
}

}
}

#endif // _SERIALIZATION_ARCHIVE_H_
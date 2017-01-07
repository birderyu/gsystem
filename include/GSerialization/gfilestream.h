// ÎÄ¼þÁ÷
#ifndef _CORE_FILE_STREAM_H_
#define _CORE_FILE_STREAM_H_

#include "gstream.h"

class GFile;

class GAPI GFileStream
	: virtual public GStream
{
public:
	GFileStream(GFile &file);
	virtual ~GFileStream() = 0;
	gbool HasFile() const;

private:
	GFile &m_rFile;
};

#endif // _CORE_FILE_STREAM_H_
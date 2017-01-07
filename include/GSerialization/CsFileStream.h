// ÎÄ¼þÁ÷
#ifndef _CORE_FILE_STREAM_H_
#define _CORE_FILE_STREAM_H_

#include "CsStream.h"

class GFile;

class GAPI CsFileStream
	: virtual public CsStream
{
public:
	CsFileStream(GFile &file);
	virtual ~CsFileStream() = 0;
	gbool HasFile() const;

private:
	GFile &m_rFile;
};

#endif // _CORE_FILE_STREAM_H_
// ÎÄ¼þÁ÷
#ifndef _CORE_FILE_STREAM_H_
#define _CORE_FILE_STREAM_H_

#include "CsStream.h"

class CsFile;

class CS_API CsFileStream
	: virtual public CsStream
{
public:
	CsFileStream(CsFile &file);
	virtual ~CsFileStream() = 0;
	cs_bool HasFile() const;

private:
	CsFile &m_rFile;
};

#endif // _CORE_FILE_STREAM_H_
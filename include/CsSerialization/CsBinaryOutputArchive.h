#ifndef _CORE_OUTPUT_BINARY_ARCHIVE_H_
#define _CORE_OUTPUT_BINARY_ARCHIVE_H_

#include "CsOutputArchive.h"
#include "CsBytes.h"

class CsBinaryOutputArchive
	: public CsOutputArchive
{
public:
	CsBinaryOutputArchive(CsFile &);

private:
	CsBytes m_tBuffer;
};

#endif // _CORE_OUTPUT_BINARY_ARCHIVE_H_
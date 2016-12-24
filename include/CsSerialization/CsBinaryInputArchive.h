#ifndef _CORE_INPUT_BINARY_ARCHIVE_H_
#define _CORE_INPUT_BINARY_ARCHIVE_H_

#include "CsInputArchive.h"
#include "CsBytes.h"

class CsBinaryInputArchive
	: public CsInputArchive
{
public:
	CsBinaryInputArchive(CsFile &);

private:
	CsBytes m_tBuffer;
};

#endif // _CORE_INPUT_BINARY_ARCHIVE_H_
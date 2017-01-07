#ifndef _CORE_INPUT_BINARY_ARCHIVE_H_
#define _CORE_INPUT_BINARY_ARCHIVE_H_

#include "CsInputArchive.h"
#include "gbytes.h"

class CsBinaryInputArchive
	: public CsInputArchive
{
public:
	CsBinaryInputArchive(GFile &);

private:
	GBytes m_tBuffer;
};

#endif // _CORE_INPUT_BINARY_ARCHIVE_H_
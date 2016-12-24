#ifndef _CORE_OUTPUT_ARCHIVE_H_
#define _CORE_OUTPUT_ARCHIVE_H_

#include "CsArchive.h"

class CS_API CsOutputArchive
	: public CsArchive
{
public:
	CsOutputArchive(CsFile &);
};

#endif // _CORE_OUTPUT_ARCHIVE_H_
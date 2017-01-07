#ifndef _CORE_OUTPUT_ARCHIVE_H_
#define _CORE_OUTPUT_ARCHIVE_H_

#include "CsArchive.h"

class GAPI CsOutputArchive
	: public CsArchive
{
public:
	CsOutputArchive(GFile &);
};

#endif // _CORE_OUTPUT_ARCHIVE_H_
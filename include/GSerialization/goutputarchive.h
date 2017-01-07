#ifndef _CORE_OUTPUT_ARCHIVE_H_
#define _CORE_OUTPUT_ARCHIVE_H_

#include "garchive.h"

class GOutputStream;

class GAPI GOutputArchive
	: public GArchive
{
public:
	GOutputArchive(GOutputStream &);
};

#endif // _CORE_OUTPUT_ARCHIVE_H_
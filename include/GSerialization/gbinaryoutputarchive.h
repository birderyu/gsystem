#ifndef _CORE_OUTPUT_BINARY_ARCHIVE_H_
#define _CORE_OUTPUT_BINARY_ARCHIVE_H_

#include "goutputarchive.h"

class GBinaryOutputStream;

class GBinaryOutputArchive
	: public GOutputArchive
{
public:
	GBinaryOutputArchive(GBinaryOutputStream &);
};

#endif // _CORE_OUTPUT_BINARY_ARCHIVE_H_
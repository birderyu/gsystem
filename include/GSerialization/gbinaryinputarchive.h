#ifndef _CORE_INPUT_BINARY_ARCHIVE_H_
#define _CORE_INPUT_BINARY_ARCHIVE_H_

#include "ginputarchive.h"

class GBinaryInputStream;

class GBinaryInputArchive
	: public GInputArchive
{
public:
	GBinaryInputArchive(GBinaryInputStream &);
};

#endif // _CORE_INPUT_BINARY_ARCHIVE_H_
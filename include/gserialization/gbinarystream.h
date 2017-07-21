// 二进制流
#ifndef _CORE_BINARY_STREAM_H_
#define _CORE_BINARY_STREAM_H_

#include "gstream.h"
#include "GCore/gbytes.h"

class GAPI GBinaryStream
	: virtual public GStream
{
public:
	virtual ~GBinaryStream() = 0;
	gbool IsBinary() const;

	virtual GBytes ToBytes() const = 0;
};

#endif // _CORE_BINARY_STREAM_H_
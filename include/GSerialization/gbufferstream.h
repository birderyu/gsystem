// »º³åÁ÷
#ifndef _CORE_BUFFER_STREAM_H_
#define _CORE_BUFFER_STREAM_H_

#include "gstream.h"

class GAPI GBufferStream
	: virtual public GStream
{
public:
	virtual ~GBufferStream() = 0;
	gbool HasBuffer() const;
};

#endif // _CORE_BUFFER_STREAM_H_
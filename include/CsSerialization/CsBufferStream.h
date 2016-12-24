// »º³åÁ÷
#ifndef _CORE_BUFFER_STREAM_H_
#define _CORE_BUFFER_STREAM_H_

#include "CsStream.h"

class CS_API CsBufferStream
	: virtual public CsStream
{
public:
	virtual ~CsBufferStream() = 0;
	cs_bool HasBuffer() const;
};

#endif // _CORE_BUFFER_STREAM_H_
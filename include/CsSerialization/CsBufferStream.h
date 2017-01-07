// »º³åÁ÷
#ifndef _CORE_BUFFER_STREAM_H_
#define _CORE_BUFFER_STREAM_H_

#include "CsStream.h"

class GAPI CsBufferStream
	: virtual public CsStream
{
public:
	virtual ~CsBufferStream() = 0;
	gbool HasBuffer() const;
};

#endif // _CORE_BUFFER_STREAM_H_
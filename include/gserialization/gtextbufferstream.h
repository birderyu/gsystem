// ÎÄ±¾»º³åÁ÷
#ifndef _CORE_TEXT_BUFFER_STREAM_H_
#define _CORE_TEXT_BUFFER_STREAM_H_

#include "gtextstream.h"
#include "gbufferstream.h"

class GAPI GTextBufferStream
	: virtual public GTextStream
	, virtual public GBufferStream
{
public:
	virtual ~GTextBufferStream() = 0;

private:
	//GStringBuffer m_tBuffer;
};

#endif // _CORE_BINARY_STREAM_H_
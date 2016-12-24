// ÎÄ±¾»º³åÁ÷
#ifndef _CORE_TEXT_BUFFER_STREAM_H_
#define _CORE_TEXT_BUFFER_STREAM_H_

#include "CsTextStream.h"
#include "CsBufferStream.h"

class CS_API CsTextBufferStream
	: virtual public CsTextStream
	, virtual public CsBufferStream
{
public:
	virtual ~CsTextBufferStream() = 0;

private:
	//CsStringBuffer m_tBuffer;
};

#endif // _CORE_BINARY_STREAM_H_
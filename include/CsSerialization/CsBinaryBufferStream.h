// 二进制缓冲流
#ifndef _CORE_BINARY_BUFFER_STREAM_H_
#define _CORE_BINARY_BUFFER_STREAM_H_

#include "CsBinaryStream.h"
#include "CsBufferStream.h"

class CS_API CsBinaryBufferStream
	: virtual public CsBinaryStream
	, virtual public CsBufferStream
{
public:
	virtual ~CsBinaryBufferStream() = 0;

private:
	CsBytes m_tBuffer;
};

#endif // _CORE_BINARY_STREAM_H_
// 二进制缓冲流
#ifndef _CORE_BINARY_BUFFER_STREAM_H_
#define _CORE_BINARY_BUFFER_STREAM_H_

#include "gbinarystream.h"
#include "gbufferstream.h"
#include "GCore/gbytebuffer.h"

class GAPI GBinaryBufferStream
	: virtual public GBinaryStream
	, virtual public GBufferStream
{
public:
	virtual ~GBinaryBufferStream() = 0;

private:
	GByteBuffer m_tBuffer;
};

#endif // _CORE_BINARY_STREAM_H_
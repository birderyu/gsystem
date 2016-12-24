#ifndef _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_
#define _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_

#include "CsBinaryBufferStream.h"
#include "CsInputStream.h"

class CS_API CsBinaryBufferInputStream
	: virtual public CsBinaryBufferStream
	, virtual public CsInputStream
{

};

#endif // _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_
#ifndef _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_
#define _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_

#include "gbinarybufferstream.h"
#include "ginputstream.h"

class GAPI GBinaryBufferInputStream
	: virtual public GBinaryBufferStream
	, virtual public GInputStream
{

};

#endif // _SERIALIZATION_BINARY_BUFFER_INPUT_STREAM_H_
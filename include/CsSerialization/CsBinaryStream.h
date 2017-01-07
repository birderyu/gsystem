// 二进制流
#ifndef _CORE_BINARY_STREAM_H_
#define _CORE_BINARY_STREAM_H_

#include "CsStream.h"
#include "gbytes.h"

class GAPI CsBinaryStream
	: virtual public CsStream
{
public:
	virtual ~CsBinaryStream() = 0;
	gbool IsBinary() const;

	virtual GBytes ToBytes() const = 0;
};

#endif // _CORE_BINARY_STREAM_H_
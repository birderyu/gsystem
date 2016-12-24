// 二进制流
#ifndef _CORE_BINARY_STREAM_H_
#define _CORE_BINARY_STREAM_H_

#include "CsStream.h"
#include "CsBytes.h"

class CS_API CsBinaryStream
	: virtual public CsStream
{
public:
	virtual ~CsBinaryStream() = 0;
	cs_bool IsBinary() const;

	virtual CsBytes ToBytes() const = 0;
};

#endif // _CORE_BINARY_STREAM_H_
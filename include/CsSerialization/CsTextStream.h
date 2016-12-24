// ÎÄ±¾Á÷
#ifndef _CORE_TEXT_STREAM_H_
#define _CORE_TEXT_STREAM_H_

#include "CsStream.h"
#include "CsString.h"

class CS_API CsTextStream
	: virtual public CsStream
{
public:
	virtual ~CsTextStream() = 0;
	cs_bool IsBinary() const;

	virtual CsString ToString() const = 0;
};

#endif // _CORE_TEXT_STREAM_H_
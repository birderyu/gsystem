// ÎÄ±¾Á÷
#ifndef _CORE_TEXT_STREAM_H_
#define _CORE_TEXT_STREAM_H_

#include "CsStream.h"
#include "gstring.h"

class GAPI CsTextStream
	: virtual public CsStream
{
public:
	virtual ~CsTextStream() = 0;
	gbool IsBinary() const;

	virtual GString ToString() const = 0;
};

#endif // _CORE_TEXT_STREAM_H_
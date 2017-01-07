//  ‰»Î ‰≥ˆ¡˜
#ifndef _CORE_INPUT_OUTPUT_STREAM_H_
#define _CORE_INPUT_OUTPUT_STREAM_H_

#include "CsInputStream.h"
#include "CsOutputStream.h"

class GAPI CsInputOutputStream
	: virtual public CsInputStream
	, virtual public CsOutputStream
{
public:
	virtual ~CsInputOutputStream() = 0;
};

#endif // _CORE_INPUT_OUTPUT_STREAM_H_
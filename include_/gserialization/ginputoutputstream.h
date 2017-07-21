//  ‰»Î ‰≥ˆ¡˜
#ifndef _CORE_INPUT_OUTPUT_STREAM_H_
#define _CORE_INPUT_OUTPUT_STREAM_H_

#include "ginputstream.h"
#include "goutputstream.h"

class GAPI GInputOutputStream
	: virtual public GInputStream
	, virtual public GOutputStream
{
public:
	virtual ~GInputOutputStream() = 0;
};

#endif // _CORE_INPUT_OUTPUT_STREAM_H_
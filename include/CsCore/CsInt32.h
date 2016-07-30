#ifndef _CSCORE_CSINT32_H_
#define _CSCORE_CSINT32_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsCore_Export CsInt32 : public CsObject
{
public:
	CsInt32(const cs_int32 nValue);

public:
	enum { CLASSCODE = CORE_CLASSCODE_INT32, };
};

typedef CsInt32 CsInteger;

#endif // _CSCORE_CSINT32_H_

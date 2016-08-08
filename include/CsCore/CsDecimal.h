#ifndef _CSCORE_DECIMAL_H_
#define _CSCORE_DECIMAL_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CS_CORE_EXPORT CsDecimal : public CsObject
{
public:
	CsDecimal(const cs_decimal nValue);

public:
	enum { CLASSCODE = CORE_CLASSCODE_INT32, };
};

typedef CsInt32 CsInteger;

#endif // _CSCORE_CSINT32_H_

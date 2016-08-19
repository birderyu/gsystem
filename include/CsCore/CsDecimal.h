/// 高精度浮点数

#ifndef _CORE_DECIMAL_H_
#define _CORE_DECIMAL_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CS_CORE_EXPORT CsDecimal : public CsObject
{
public:
	CsDecimal(const cs_decimal nValue);

public:
	enum { CLASSCODE = CORE_CLASSCODE_INT32, };
};

#endif // _CORE_DECIMAL_H_

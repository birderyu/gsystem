#ifndef _CORE_LONG_INTEGER_H_
#define _CORE_LONG_INTEGER_H_

#include "CsPackage.h"

class CS_API CsLongInteger 
	: public CsNumber<cs_long>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_LONG_INTEGER, };

public:
	static cs_long MaxValue();
	static cs_long MinValue();
	static CsLongInteger ValueOf(const CsString &);

public:
	CsLongInteger(cs_long val = 0L);
	CsLongInteger(const CsLongInteger &);

	cs_uint ClassCode() const;
};

typedef CsLongInteger CsLongInt;
typedef CsLongInteger CsLong;

#endif // _CORE_LONG_INTEGER_H_
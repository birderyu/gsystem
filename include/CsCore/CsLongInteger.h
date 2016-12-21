#ifndef _CORE_LONG_INTEGER_H_
#define _CORE_LONG_INTEGER_H_

#include "CsPackage.h"

class CS_API CsLongInteger 
	: public CsNumber<cs_long>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_INTEGER, };

public:
	static cs_int MaxValue();
	static cs_int MinValue();
	static CsLongInteger ValueOf(const CsString &);

public:
	CsLongInteger(cs_long val = 0L);
	CsLongInteger(const CsLongInteger &);

	cs_uint ClassCode() const;
};

typedef CsLongInteger CsLongInt;
typedef CsLongInteger CsLong;

#endif // _CORE_LONG_INTEGER_H_
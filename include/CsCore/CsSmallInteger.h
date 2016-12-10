#ifndef _CORE_SMALL_INTEGER_H_
#define _CORE_SMALL_INTEGER_H_

#include "CsPackage.h"

class CS_API CsSmallInteger 
	: public CsNumber<cs_small>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_SMALL_INTEGER, };

public:
	static cs_small MaxValue();
	static cs_small MinValue();
	static CsSmallInteger ValueOf(const CsString &);

public:
	CsSmallInteger(cs_small val = 0);
	CsSmallInteger(const CsSmallInteger &);

	cs_uint ClassCode() const;
};

typedef CsSmallInteger CsSmallInt;
typedef CsSmallInteger CsSmall;
typedef CsSmallInteger CsInteger8;
typedef CsSmallInteger CsInt8;

#endif // _CORE_SMALL_INTEGER_H_
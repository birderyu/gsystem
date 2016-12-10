#ifndef _CORE_INTEGER_H_
#define _CORE_INTEGER_H_

#include "CsPackage.h"

class CS_API CsInteger 
	: public CsNumber<cs_int>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_INTEGER, };

public:
	static cs_int MaxValue();
	static cs_int MinValue();
	static CsInteger ValueOf(const CsString &);

public:
	CsInteger(cs_int val = 0);
	CsInteger(const CsInteger &);

	cs_uint ClassCode() const;
};

typedef CsInteger CsInt;
typedef CsInteger CsInteger32;
typedef CsInteger CsInt32;

#endif // _CORE_INTEGER_H_
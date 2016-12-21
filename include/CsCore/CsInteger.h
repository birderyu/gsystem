#ifndef _CORE_INTEGER_H_
#define _CORE_INTEGER_H_

#include "CsPackage.h"

class CS_API CsInteger 
	: public CsNumber<cs_int>
{
public:
	enum { CLASS_CODE = CLASS_CODE_INTEGER, };

public:
	static const cs_size_t MAX_VALUE = CS_INT32_MAX;
	static const cs_size_t MIN_VALUE = CS_INT32_MIN;

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
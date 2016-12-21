#ifndef _CORE_UNSIGNED_INTEGER_H_
#define _CORE_UNSIGNED_INTEGER_H_

#include "CsPackage.h"

class CS_API CsUnsignedInteger 
	: public CsNumber<cs_uint>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_INTEGER, };

public:
	static cs_uint MaxValue();
	static cs_uint MinValue();
	static CsUnsignedInteger ValueOf(const CsString &);

public:
	CsUnsignedInteger(cs_uint val = 0);
	CsUnsignedInteger(const CsUnsignedInteger &);
	virtual ~CsUnsignedInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsUnsignedInteger CsUnsignedInt;
typedef CsUnsignedInteger CsUInteger;
typedef CsUnsignedInteger CsUInt;
typedef CsUnsignedInteger CsUnsignedInteger32;
typedef CsUnsignedInteger CsUInteger32;
typedef CsUnsignedInteger CsUnsignedInt32;
typedef CsUnsignedInteger CsUInt32;

#endif // _CORE_UNSIGNED_INTEGER_H_
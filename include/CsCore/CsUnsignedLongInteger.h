#ifndef _CORE_UNSIGNED_LONG_INTEGER_H_
#define _CORE_UNSIGNED_LONG_INTEGER_H_

#include "CsPackage.h"

class CS_API CsUnsignedLongInteger 
	: public CsNumber<cs_ulong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_LONG_INTEGER, };

public:
	static cs_ulong MaxValue();
	static cs_ulong MinValue();
	static CsUnsignedLongInteger ValueOf(const CsString &);

public:
	CsUnsignedLongInteger(cs_ulong val = 0UL);
	CsUnsignedLongInteger(const CsUnsignedLongInteger &);

	cs_uint ClassCode() const;
};

typedef CsUnsignedLongInteger CsUnsignedLongInt;
typedef CsUnsignedLongInteger CsULongInteger;
typedef CsUnsignedLongInteger CsULongInt;
typedef CsUnsignedLongInteger CsUnsignedLong;
typedef CsUnsignedLongInteger CsULong;

#endif // _CORE_UNSIGNED_LONG_INTEGER_H_
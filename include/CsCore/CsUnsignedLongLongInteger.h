#ifndef _CORE_UNSIGNED_LONG_LONG_INTEGER_H_
#define _CORE_UNSIGNED_LONG_LONG_INTEGER_H_

#include "CsPackage.h"

class CS_API CsUnsignedLongLongInteger 
	: public CsNumber<cs_ulonglong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER, };

public:
	static cs_ulonglong MaxValue();
	static cs_ulonglong MinValue();
	static CsUnsignedLongLongInteger ValueOf(const CsString &);

public:
	CsUnsignedLongLongInteger(cs_ulonglong val = 0LL);
	CsUnsignedLongLongInteger(const CsUnsignedLongLongInteger &);
	virtual ~CsUnsignedLongLongInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsUnsignedLongLongInteger CsUnsignedLongLongInt;
typedef CsUnsignedLongLongInteger CsULongLongInteger;
typedef CsUnsignedLongLongInteger CsULongLongInt;
typedef CsUnsignedLongLongInteger CsUnsignedLongLong;
typedef CsUnsignedLongLongInteger CsULongLong;
typedef CsUnsignedLongLongInteger CsUnsignedInteger64;
typedef CsUnsignedLongLongInteger CsUInteger64;
typedef CsUnsignedLongLongInteger CsUnsignedInt64;
typedef CsUnsignedLongLongInteger CsUInt64;

#endif // _CORE_UNSIGNED_LONG_INTEGER_H_
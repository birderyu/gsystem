#ifndef _CORE_UNSIGNED_SMALL_INTEGER_H_
#define _CORE_UNSIGNED_SMALL_INTEGER_H_

#include "CsUnsignedCharacter.h"

class CS_API CsUnsignedSmallInteger 
	: public CsNumber<cs_usmall>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_SMALL_INTEGER, };

public:
	static cs_usmall MaxValue();
	static cs_usmall MinValue();
	static CsUnsignedSmallInteger ValueOf(const CsString &);

public:
	CsUnsignedSmallInteger(cs_usmall val = 0);
	CsUnsignedSmallInteger(const CsUnsignedSmallInteger &);
	virtual ~CsUnsignedSmallInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsUnsignedSmallInteger CsUnsignedSmallInt;
typedef CsUnsignedSmallInteger CsUSmallInteger;
typedef CsUnsignedSmallInteger CsUSmallInt;
typedef CsUnsignedSmallInteger CsUSmall;
typedef CsUnsignedSmallInteger CsUnsignedInteger8;
typedef CsUnsignedSmallInteger CsUInteger8;
typedef CsUnsignedSmallInteger CsUnsignedInt8;
typedef CsUnsignedSmallInteger CsUInt8;

#endif // _CORE_UNSIGNED_SMALL_INTEGER_H_
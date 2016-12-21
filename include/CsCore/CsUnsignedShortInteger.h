#ifndef _CORE_UNSIGNED_SHORT_INTEGER_H_
#define _CORE_UNSIGNED_SHORT_INTEGER_H_

#include "CsPackage.h"

class CS_API CsUnsignedShortInteger 
	: public CsNumber<cs_ushort>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_SHORT_INTEGER, };

public:
	static cs_ushort MaxValue();
	static cs_ushort MinValue();
	static CsUnsignedShortInteger ValueOf(const CsString &);

public:
	CsUnsignedShortInteger(cs_ushort val = 0);
	CsUnsignedShortInteger(const CsUnsignedShortInteger &);
	virtual ~CsUnsignedShortInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsUnsignedShortInteger CsUnsignedShortInt;
typedef CsUnsignedShortInteger CsUShortInteger;
typedef CsUnsignedShortInteger CsUShortInt;
typedef CsUnsignedShortInteger CsUShort;
typedef CsUnsignedShortInteger CsUnsignedInteger16;
typedef CsUnsignedShortInteger CsUInteger16;
typedef CsUnsignedShortInteger CsUnsignedInt16;
typedef CsUnsignedShortInteger CsUInt16;

#endif // _CORE_UNSIGNED_SHORT_INTEGER_H_
#ifndef _CORE_SHORT_INTEGER_H_
#define _CORE_SHORT_INTEGER_H_

#include "CsPackage.h"

class CS_API CsShortInteger 
	: public CsNumber<cs_short>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_SHORT_INTEGER, };

public:
	static cs_short MaxValue();
	static cs_short MinValue();
	static CsShortInteger ValueOf(const CsString &);

public:
	CsShortInteger(cs_short val = 0);
	CsShortInteger(const CsShortInteger &);
	virtual ~CsShortInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsShortInteger CsShortInt;
typedef CsShortInteger CsShort;
typedef CsShortInteger CsInteger16;
typedef CsShortInteger CsInt16;

#endif // _CORE_SHORT_INTEGER_H_
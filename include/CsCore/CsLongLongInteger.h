#ifndef _CORE_LONG_LONG_INTEGER_H_
#define _CORE_LONG_LONG_INTEGER_H_

#include "CsPackage.h"

class CS_API CsLongLongInteger 
	: public CsNumber<cs_longlong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_LONG_INTEGER, };

public:
	static cs_longlong MaxValue();
	static cs_longlong MinValue();
	static CsLongLongInteger ValueOf(const CsString &);

public:
	CsLongLongInteger(cs_longlong val = 0LL);
	CsLongLongInteger(const CsLongLongInteger &);
	virtual ~CsLongLongInteger();

	virtual cs_uint ClassCode() const;
};

typedef CsLongLongInteger CsLongLongInt;
typedef CsLongLongInteger CsLongLong;
typedef CsLongLongInteger CsInteger64;
typedef CsLongLongInteger CsInt64;

#endif // _CORE_LONG_INTEGER_H_
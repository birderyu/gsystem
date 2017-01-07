#ifndef _CORE_UNSIGNED_LONG_LONG_INTEGER_H_
#define _CORE_UNSIGNED_LONG_LONG_INTEGER_H_

#include "gpackage.h"

class GAPI GUnsignedLongLongInteger 
	: public GNumber<gulonglong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER, };

public:
	static gulonglong MaxValue();
	static gulonglong MinValue();
	static GUnsignedLongLongInteger ValueOf(const GString &);

public:
	GUnsignedLongLongInteger(gulonglong val = 0LL);
	GUnsignedLongLongInteger(const GUnsignedLongLongInteger &);
	virtual ~GUnsignedLongLongInteger();

	virtual guint ClassCode() const;
};

typedef GUnsignedLongLongInteger GUnsignedLongLongInt;
typedef GUnsignedLongLongInteger GULongLongInteger;
typedef GUnsignedLongLongInteger GULongLongInt;
typedef GUnsignedLongLongInteger GUnsignedLongLong;
typedef GUnsignedLongLongInteger GULongLong;
typedef GUnsignedLongLongInteger GUnsignedInteger64;
typedef GUnsignedLongLongInteger GUInteger64;
typedef GUnsignedLongLongInteger GUnsignedInt64;
typedef GUnsignedLongLongInteger GUInt64;

#endif // _CORE_UNSIGNED_LONG_INTEGER_H_
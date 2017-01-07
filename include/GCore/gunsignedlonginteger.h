#ifndef _CORE_UNSIGNED_LONG_INTEGER_H_
#define _CORE_UNSIGNED_LONG_INTEGER_H_

#include "gpackage.h"

class GAPI GUnsignedLongInteger 
	: public GNumber<gulong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_LONG_INTEGER, };

public:
	static gulong MaxValue();
	static gulong MinValue();
	static GUnsignedLongInteger ValueOf(const GString &);

public:
	GUnsignedLongInteger(gulong val = 0UL);
	GUnsignedLongInteger(const GUnsignedLongInteger &);

	guint ClassCode() const;
};

typedef GUnsignedLongInteger GUnsignedLongInt;
typedef GUnsignedLongInteger GULongInteger;
typedef GUnsignedLongInteger GULongInt;
typedef GUnsignedLongInteger GUnsignedLong;
typedef GUnsignedLongInteger GULong;

#endif // _CORE_UNSIGNED_LONG_INTEGER_H_
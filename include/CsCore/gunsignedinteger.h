#ifndef _CORE_UNSIGNED_INTEGER_H_
#define _CORE_UNSIGNED_INTEGER_H_

#include "gpackage.h"

class GAPI GUnsignedInteger 
	: public GNumber<guint>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_INTEGER, };

public:
	static guint MaxValue();
	static guint MinValue();
	static GUnsignedInteger ValueOf(const GString &);

public:
	GUnsignedInteger(guint val = 0);
	GUnsignedInteger(const GUnsignedInteger &);
	virtual ~GUnsignedInteger();

	virtual guint ClassCode() const;
};

typedef GUnsignedInteger GUnsignedInt;
typedef GUnsignedInteger GUInteger;
typedef GUnsignedInteger GUInt;
typedef GUnsignedInteger GUnsignedInteger32;
typedef GUnsignedInteger GUInteger32;
typedef GUnsignedInteger GUnsignedInt32;
typedef GUnsignedInteger GUInt32;

#endif // _CORE_UNSIGNED_INTEGER_H_
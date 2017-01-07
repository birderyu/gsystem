#ifndef _CORE_UNSIGNED_SHORT_INTEGER_H_
#define _CORE_UNSIGNED_SHORT_INTEGER_H_

#include "gpackage.h"

class GAPI GUnsignedShortInteger 
	: public GNumber<gushort>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_SHORT_INTEGER, };

public:
	static gushort MaxValue();
	static gushort MinValue();
	static GUnsignedShortInteger ValueOf(const GString &);

public:
	GUnsignedShortInteger(gushort val = 0);
	GUnsignedShortInteger(const GUnsignedShortInteger &);
	virtual ~GUnsignedShortInteger();

	virtual guint ClassCode() const;
};

typedef GUnsignedShortInteger GUnsignedShortInt;
typedef GUnsignedShortInteger GUShortInteger;
typedef GUnsignedShortInteger GUShortInt;
typedef GUnsignedShortInteger GUShort;
typedef GUnsignedShortInteger GUnsignedInteger16;
typedef GUnsignedShortInteger GUInteger16;
typedef GUnsignedShortInteger GUnsignedInt16;
typedef GUnsignedShortInteger GUInt16;

#endif // _CORE_UNSIGNED_SHORT_INTEGER_H_
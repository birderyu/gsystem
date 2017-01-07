#ifndef _CORE_SHORT_INTEGER_H_
#define _CORE_SHORT_INTEGER_H_

#include "gpackage.h"

class GAPI GShortInteger 
	: public GNumber<gshort>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SHORT_INTEGER, };

public:
	static gshort MaxValue();
	static gshort MinValue();
	static GShortInteger ValueOf(const GString &);

public:
	GShortInteger(gshort val = 0);
	GShortInteger(const GShortInteger &);
	virtual ~GShortInteger();

	virtual guint ClassCode() const;
};

typedef GShortInteger GShortInt;
typedef GShortInteger GShort;
typedef GShortInteger GInteger16;
typedef GShortInteger GInt16;

#endif // _CORE_SHORT_INTEGER_H_
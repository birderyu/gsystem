#ifndef _CORE_SMALL_INTEGER_H_
#define _CORE_SMALL_INTEGER_H_

#include "gpackage.h"

class GAPI GSmallInteger 
	: public GNumber<gsmall>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SMALL_INTEGER, };

public:
	static gsmall MaxValue();
	static gsmall MinValue();
	static GSmallInteger ValueOf(const GString &);

public:
	GSmallInteger(gsmall val = 0);
	GSmallInteger(const GSmallInteger &);

	guint ClassCode() const;
};

typedef GSmallInteger GSmallInt;
typedef GSmallInteger GSmall;
typedef GSmallInteger GInteger8;
typedef GSmallInteger GInt8;

#endif // _CORE_SMALL_INTEGER_H_
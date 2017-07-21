#ifndef _CORE_SMALL_INTEGER_H_
#define _CORE_SMALL_INTEGER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GSmallInteger 
	: public GNumber<gsmall>
{
public:
	static gsmall MaxValue();
	static gsmall MinValue();
	static GSmallInteger ValueOf(const GString &);

public:
	GSmallInteger(gsmall val = 0);
	GSmallInteger(const GSmallInteger &);

	guint ClassCode() const GNOEXCEPT;
};

typedef GSmallInteger GSmallInt;
typedef GSmallInteger GSmall;
typedef GSmallInteger GInteger8;
typedef GSmallInteger GInt8;

} // namespace gsystem

#endif // _CORE_SMALL_INTEGER_H_
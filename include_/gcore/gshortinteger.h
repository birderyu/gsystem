#ifndef _CORE_SHORT_INTEGER_H_
#define _CORE_SHORT_INTEGER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GShortInteger 
	: public GNumber<gshort>
{
public:
	static gshort MaxValue();
	static gshort MinValue();
	static GShortInteger ValueOf(const GString &);

public:
	GShortInteger(gshort val = 0);
	GShortInteger(const GShortInteger &);
	virtual ~GShortInteger();

	virtual guint ClassCode() const GNOEXCEPT;
};

typedef GShortInteger GShortInt;
typedef GShortInteger GShort;
typedef GShortInteger GInteger16;
typedef GShortInteger GInt16;

} // namespace gsystem

#endif // _CORE_SHORT_INTEGER_H_
#ifndef _CORE_LONG_INTEGER_H_
#define _CORE_LONG_INTEGER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GLongInteger 
	: public GNumber<glong>
{
public:
	static gint MaxValue();
	static gint MinValue();
	static GLongInteger ValueOf(const GString &);

public:
	GLongInteger(glong val = 0L);
	GLongInteger(const GLongInteger &);

	guint ClassCode() const GNOEXCEPT;
};

typedef GLongInteger GLongInt;
typedef GLongInteger GLong;

} // namespace gsystem

#endif // _CORE_LONG_INTEGER_H_
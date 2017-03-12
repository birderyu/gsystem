#ifndef _CORE_LONG_INTEGER_H_
#define _CORE_LONG_INTEGER_H_

#include "gpackage.h"

namespace gnova {

class GAPI GLongInteger 
	: public GNumber<glong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_INTEGER, };

public:
	static gint MaxValue();
	static gint MinValue();
	static GLongInteger ValueOf(const GString &);

public:
	GLongInteger(glong val = 0L);
	GLongInteger(const GLongInteger &);

	guint ClassCode() const;
};

typedef GLongInteger GLongInt;
typedef GLongInteger GLong;

}

#endif // _CORE_LONG_INTEGER_H_
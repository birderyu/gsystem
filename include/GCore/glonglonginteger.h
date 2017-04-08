#ifndef _CORE_LONG_LONG_INTEGER_H_
#define _CORE_LONG_LONG_INTEGER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GLongLongInteger 
	: public GNumber<glonglong>
{
public:
	static glonglong MaxValue();
	static glonglong MinValue();
	static GLongLongInteger ValueOf(const GString &);

public:
	GLongLongInteger(glonglong val = 0LL);
	GLongLongInteger(const GLongLongInteger &);
	virtual ~GLongLongInteger();

	virtual guint ClassCode() const;
};

typedef GLongLongInteger GLongLongInt;
typedef GLongLongInteger GLongLong;
typedef GLongLongInteger GInteger64;
typedef GLongLongInteger GInt64;

} // namespace gsystem

#endif // _CORE_LONG_INTEGER_H_
#ifndef _CORE_LONG_LONG_INTEGER_H_
#define _CORE_LONG_LONG_INTEGER_H_

#include "gpackage.h"

class GAPI GLongLongInteger 
	: public GNumber<glonglong>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_LONG_INTEGER, };

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

#endif // _CORE_LONG_INTEGER_H_
#ifndef _CORE_INTEGER_H_
#define _CORE_INTEGER_H_

#include "gpackage.h"

G_BEGIN_NAMESPACE

class GAPI GInteger 
	: public GNumber<gint>
{
public:
	enum { CLASS_CODE = CLASS_CODE_INTEGER, };

public:
	static const gsize MAX_VALUE = G_INT32_MAX;
	static const gsize MIN_VALUE = G_INT32_MIN;

	static gint MaxValue();
	static gint MinValue();
	static GInteger ValueOf(const GString &);

public:
	GInteger(gint val = 0);
	GInteger(const GInteger &);

	guint ClassCode() const;
};

typedef GInteger GInt;
typedef GInteger GInteger32;
typedef GInteger GInt32;

G_END_NAMESPACE

#endif // _CORE_INTEGER_H_
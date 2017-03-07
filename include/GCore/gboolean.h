#ifndef _CORE_BOOLEAN_H_
#define _CORE_BOOLEAN_H_

#include "gpackage.h"

G_BEGIN_NAMESPACE

class GAPI GBoolean 
	: public GPackage<gbool>
{
public:
	enum { CLASS_CODE = CLASS_CODE_BOOLEAN, };

public:
	static GBoolean ValueOf(const GString &);

public:
	GBoolean(gbool val = false);
	GBoolean(const GBoolean &);

	guint ClassCode() const;
};

typedef GBoolean GBool;

G_END_NAMESPACE

#endif // _CORE_BOOLEAN_H_
#ifndef _CORE_BOOLEAN_H_
#define _CORE_BOOLEAN_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GBoolean 
	: public GPackage<gbool>
{
public:
	static GBoolean ValueOf(const GString &);

public:
	GBoolean(gbool val = false);
	GBoolean(const GBoolean &);

	guint ClassCode() const;
};

typedef GBoolean GBool;

} // namespace gsystem

#endif // _CORE_BOOLEAN_H_
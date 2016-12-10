#ifndef _CORE_BOOLEAN_H_
#define _CORE_BOOLEAN_H_

#include "CsPackage.h"

class CS_API CsBoolean 
	: public CsPackage<cs_bool>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_BOOLEAN, };

public:
	static CsBoolean ValueOf(const CsString &);

public:
	CsBoolean(cs_bool val = false);
	CsBoolean(const CsBoolean &);

	cs_uint ClassCode() const;
};

typedef CsBoolean CsBool;

#endif // _CORE_BOOLEAN_H_
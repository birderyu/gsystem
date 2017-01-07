#ifndef _CORE_NUMBER_H_
#define _CORE_NUMBER_H_

#include "gbyte.h"
#include "gboolean.h"
#include "gcharacter.h"
#include "gsignedcharacter.h"
#include "gunsignedcharacter.h"
#include "gwidecharacter.h"
#include "gsmallinteger.h"
#include "gunsignedsmallinteger.h"
#include "gshortinteger.h"
#include "gunsignedshortinteger.h"
#include "ginteger.h"
#include "gunsignedinteger.h"
#include "glonginteger.h"
#include "gunsignedlonginteger.h"
#include "glonglonginteger.h"
#include "gunsignedlonglonginteger.h"
#include "gsinglefloat.h"
#include "gdoublefloat.h"
#include "glongdoublefloat.h"

#ifdef CS_REAL_USE_FLOAT
typedef CsFloat		CsReal;
#else // CS_REAL_USE_DOUBLE
typedef GDouble	CsReal;
#endif

#endif // _CORE_NUMBER_H_
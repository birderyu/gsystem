#ifndef _CORE_NUMBER_H_
#define _CORE_NUMBER_H_

#include "CsByte.h"
#include "CsBoolean.h"
#include "CsCharacter.h"
#include "CsSignedCharacter.h"
#include "CsUnsignedCharacter.h"
#include "CsWideCharacter.h"
#include "CsSmallInteger.h"
#include "CsUnsignedSmallInteger.h"
#include "CsShortInteger.h"
#include "CsUnsignedShortInteger.h"
#include "CsInteger.h"
#include "CsUnsignedInteger.h"
#include "CsLongInteger.h"
#include "CsUnsignedLongInteger.h"
#include "CsLongLongInteger.h"
#include "CsUnsignedLongLongInteger.h"
#include "CsSingleFloat.h"
#include "CsDoubleFloat.h"
#include "CsLongDoubleFloat.h"

#ifdef CS_REAL_USE_FLOAT
typedef CsFloat		CsReal;
#else // CS_REAL_USE_DOUBLE
typedef CsDouble	CsReal;
#endif

#endif // _CORE_NUMBER_H_
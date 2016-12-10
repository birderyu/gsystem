#ifndef _CORE_DATETIME_H_
#define _CORE_DATETIME_H_

#include "CsObject.h"

class CS_API CsDateTime final 
	: public CsObject
{
public:
	cs_bool SetDate(cs_uint y, cs_uint m, cs_uint d, cs_uint dofw = 0);
	cs_bool SetTime(cs_uint h, cs_uint m, cs_uint s, cs_uint ms = 0);

	static CsDateTime Now();

};

#endif // _CORE_DATETIME_H_
#ifndef _CORE_DATE_H_
#define _CORE_DATE_H_

#include "CsObject.h"

class CS_API CsDate final 
	: public CsObject
{
public:
	CsDate(cs_uint y, cs_uint m, cs_uint d, cs_uint dofw = 0);
	cs_bool SetDate(cs_uint y, cs_uint m, cs_uint d, cs_uint dofw = 0);
	cs_uint GetYear() const;
	cs_uint GetMonth() const;
	cs_uint GetDay() const;
	cs_uint GetDayOfWeek() const;
	cs_uint GetDayOfYear() const;

	cs_int GetDaysTo(const CsDate &) const;

	static CsDate Now();

};

#endif // _CORE_DATE_H_
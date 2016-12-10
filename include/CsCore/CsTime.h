#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

#include "CsObject.h"

class CsString;

class CS_API CsTime final 
	: public CsObject
{
public:
	CsTime(cs_uint h, cs_uint m, cs_uint s, cs_uint ms = 0);

	cs_bool SetTime(cs_uint h, cs_uint m, cs_uint s, cs_uint ms = 0);

	cs_uint GetHour() const;
	cs_uint GetMinute() const;
	cs_uint GetSecond() const;
	cs_uint GetMilliSecond() const;

	cs_int GetSecsTo(const CsTime &) const;
	cs_int GetMSecsTo(const CsTime &) const;

	static CsTime Now();
};

#endif // _CORE_TIME_H_
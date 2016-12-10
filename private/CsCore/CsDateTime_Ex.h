#ifndef _CORE_DATETIME_PRIVATE_H
#define _CORE_DATETIME_PRIVATE_H

#include "CsGlobal_Ex.h"

class CsDateTime;
class CsDate;
class CsTime;

class CsDateTime_Ex
{
public:
	static cs_bool GetNow(CsDateTime &dt);
	static cs_bool GetNow(CsDate &d);
	static cs_bool GetNow(CsTime &t);

private:
	static cs_bool GetNow(cs_uint &y, cs_uint &m, cs_uint &d, cs_uint &dofw,
		cs_uint &h, cs_uint &mm, cs_uint &s, cs_uint &ms);
};

#endif // _CORE_DATETIME_PRIVATE_H
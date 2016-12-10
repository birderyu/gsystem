#include "CsDateTime_Ex.h"
#include "CsDateTime.h"
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif

cs_bool CsDateTime_Ex::GetNow(CsDateTime &dt)
{
	return false;
}

cs_bool CsDateTime_Ex::GetNow(CsDate &d)
{
	return false;
}

cs_bool CsDateTime_Ex::GetNow(CsTime &t)
{
	return false;
}

cs_bool CsDateTime_Ex::GetNow(cs_uint &y, cs_uint &m, cs_uint &d, cs_uint &dofw,
	cs_uint &h, cs_uint &mm, cs_uint &s, cs_uint &ms)
{
	cs_uint intertimep;
	cs_ushort  msecp;
	struct tm breakuptime;
	time_t tmptime;

#ifdef WIN32
	intertimep = (cs_uint)time(NULL);
	SYSTEMTIME cursystimep;
	GetSystemTime(&cursystimep);
	msecp = cursystimep.wMilliseconds;

	tmptime = (time_t)intertimep;
	errno_t errno;
	errno = localtime_s(&breakuptime, (time_t *)&tmptime);
	if (errno != 0) 
	{
		return false;
	}
#else
	struct timeval  tmptimeval;
	gettimeofday(&tmptimeval, NULL);
	intertimep = (cs_uint)tmptimeval.tv_sec;
	msecp = (cs_short)(tmptimeval.tv_usec / 1000);
	tmptime = (time_t)intertimep;
	struct tm  * ptm = localtime_r((time_t *)&tmptime, (tm *)&breakuptime);
	if (ptm == NULL)
	{
		return false
	};
#endif

	
	y = breakuptime.tm_year + 1900;
	m = breakuptime.tm_mon + 1;
	d = breakuptime.tm_mday;
	dofw = breakuptime.tm_mday;
	if (dofw == 0)
	{
		dofw = 7;
	}

	h = breakuptime.tm_hour;
	mm = breakuptime.tm_min;
	s = breakuptime.tm_sec;
	ms = msecp;
	return true;
}
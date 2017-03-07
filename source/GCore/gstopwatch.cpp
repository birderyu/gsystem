#include "gstopwatch.h"

#ifdef G_SYSTEM_WINDOWS 
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>
#else // !G_SYSTEM_WINDOWS
#include <time.h>
#endif // G_SYSTEM_WINDOWS

gvoid GStopWatch::Start()
{
	m_nStart = Tick();
}

gint GStopWatch::Pause() const
{
	return Tick() - m_nStart;
}

gint GStopWatch::Stop()
{
	gint t = Tick() - m_nStart;
	Start();
	return t;
}

gulong GStopWatch::Tick() const
{
#ifdef G_SYSTEM_WINDOWS 
	return GetTickCount();
#else // !G_SYSTEM_WINDOWS
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif // G_SYSTEM_WINDOWS
}

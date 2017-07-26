#include "gstopwatch.h"

#ifdef G_SYSTEM_WINDOWS 
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>
#else // !G_SYSTEM_WINDOWS
#include <time.h>
#endif // G_SYSTEM_WINDOWS

namespace gsystem { // gsystem

GStopWatch::GStopWatch()
{
	Start();
}

gvoid GStopWatch::Start()
{
	m_nStart = Moment();
}

gulong GStopWatch::Tick() const
{
	return Moment() - m_nStart;
}

gulong GStopWatch::Stop()
{
	gulong t = Moment() - m_nStart;
	Start();
	return t;
}

gulong GStopWatch::Moment() const
{
#ifdef G_SYSTEM_WINDOWS 
	return ::GetTickCount();
#else // !G_SYSTEM_WINDOWS
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif // G_SYSTEM_WINDOWS
}

} // namespace gsystem

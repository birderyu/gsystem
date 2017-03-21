#ifndef _CORE_QUICK_LOCK_H_
#define _CORE_QUICK_LOCK_H_

#include "glock.h"

#ifdef G_SYSTEM_WINDOWS
#include "gcriticalsection.h"
#else // !G_SYSTEM_WINDOWS
#include "gmutex.h"
#endif // G_SYSTEM_WINDOWS

namespace gsystem { // gsystem

class GAPI GQuickLock final
	: public GLock
{
public:
	gvoid Lock();
	gvoid Unlock();

private:
#ifdef G_SYSTEM_WINDOWS
	GCriticalSection m_tLock;
#else // !G_SYSTEM_WINDOWS
	GMutex m_tLock;
#endif // G_SYSTEM_WINDOWS
};

} // namespace gsystem

#endif // _CORE_QUICK_LOCK_H_
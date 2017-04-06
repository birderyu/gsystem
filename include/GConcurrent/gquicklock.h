#ifndef _CONCURRENT_QUICK_LOCK_H_
#define _CONCURRENT_QUICK_LOCK_H_

#include "GCore/glock.h"

#ifdef G_SYSTEM_WINDOWS
#include "GCore/gcriticalsection.h"
#else // !G_SYSTEM_WINDOWS
#include "GCore/gmutex.h"
#endif // G_SYSTEM_WINDOWS

namespace gsystem { // gsystem
namespace sync { // gsystem.sync

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

} // namespace gsystem.sync
} // namespace gsystem

#endif // _CONCURRENT_QUICK_LOCK_H_
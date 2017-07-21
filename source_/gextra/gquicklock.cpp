#include "gquicklock.h"

namespace gsystem { // gsystem

gvoid GQuickLock::Lock()
{
	m_tLock.Lock();
}

gvoid GQuickLock::Unlock()
{
	m_tLock.Unlock();
}

} // namespace gsystem

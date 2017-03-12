#include "gquicklock.h"

namespace gnova {

gvoid GQuickLock::Lock()
{
	m_tLock.Lock();
}

gvoid GQuickLock::Unlock()
{
	m_tLock.Unlock();
}

}
#include "gquicklock.h"

gvoid GQuickLock::Lock()
{
	m_tLock.Lock();
}

gvoid GQuickLock::Unlock()
{
	m_tLock.Unlock();
}
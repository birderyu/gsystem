#include "CsAutoLock_Private.h"
#include "CsAutoLock.h"
#include "CsMutex.h"

CsAutoLock_Private::CsAutoLock_Private(CsAutoLock *pPublic, CsMutex *pMutex)
:CsObject_Private(pPublic), m_pMutex(pMutex), m_bLocked(true)
{
	if (!m_pMutex)
	{
		return;
	}
	m_pMutex->Lock();
}

CsAutoLock_Private::~CsAutoLock_Private()
{
	Unlock();
}

void CsAutoLock_Private::Unlock()
{
	if (!m_bLocked || !m_pMutex)
	{
		return;
	}
	m_pMutex->Unlock();
	m_bLocked = false;
}
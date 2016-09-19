/// 自动锁
/// 根据传入的锁类型自动加锁

#ifndef _CORE_AUTOLOCK_H_
#define _CORE_AUTOLOCK_H_

#include "CsObject.h"

template <typename LockT>
class CS_CORE_EXPORT CsAutoLock :public CsObject
{
public:
	CsAutoLock(LockT *pLock);
	~CsAutoLock();

public:
	enum { CLASSCODE = CORE_CLASSCODE_AUTO_LOCK, };

private:
	cs_void Unlock();

	/// 锁
	LockT *m_pLock;
};

template <typename LockT>
CsAutoLock<LockT>::CsAutoLock(LockT *pLock)
: m_pLock(pLock)
{
	if (!m_pLock)
	{
		return;
	}
	m_pLock->Lock();
}

template <typename LockT>
CsAutoLock<LockT>::~CsAutoLock()
{
	Unlock();
}

template <typename LockT>
cs_void CsAutoLock<LockT>::Unlock()
{
	if (!m_pLock)
	{
		return;
	}
	m_pLock->Unlock();
}

#endif // _CORE_AUTOLOCK_H_

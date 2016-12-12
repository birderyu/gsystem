// 一个线程安全的单例模式基类

#ifndef _CORE_SINGLETON_H_
#define _CORE_SINGLETON_H_

#include "CsAutoLock.h"

template <typename ClassT, typename LockT>
class CsSingleton
{
public:
	static ClassT& Instance()
	{
		if (m_pInstance == NULL)
		{
			CsAutoLock<LockT> lock(m_tLock);
			if (m_pInstance == NULL)
			{
				m_pInstance = new ClassT;
				CsCallAtExit(Destroy);
			}
			return *m_pInstance;
		}
		return *m_pInstance;
	}

protected:
	CsSingleton() {}
	~CsSingleton() {}

private:
	CsSingleton(const CsSingleton<ClassT, LockT> &) {}
	CsSingleton &operator=(const CsSingleton<ClassT, LockT> &){}

	static cs_void Destroy()
	{
		if (m_pInstance != NULL)
			delete m_pInstance;
		m_pInstance = NULL;
	}

	static ClassT * volatile m_pInstance;
	static LockT m_tLock;
};

template <typename ClassT, typename LockT>
ClassT *volatile CsSingleton<ClassT, LockT>::m_pInstance = NULL;

template <typename ClassT, typename LockT>
LockT CsSingleton<ClassT, LockT>::m_tLock = LockT();

#endif // _CORE_SINGLETON_H_

// 一个线程安全的单例模式基类
#ifndef _CORE_SINGLETON_H_
#define _CORE_SINGLETON_H_

#include "glockguard.h"

namespace gsystem { // gsystem

template <typename ClassT, typename LockT>
class GSingleton
{
public:
	static ClassT& Instance()
	{
		if (m_pInstance == GNULL)
		{
			GLockGuard<LockT> lock(m_tLock);
			if (m_pInstance == GNULL)
			{
				// 特殊场景下，可能会有内存泄漏的风险
				ClassT *ptr = new ClassT();
				ptr->Initialize();
				m_pInstance = ptr;
				G_CALL_AT_EXIT(Destroy);
			}
			return *m_pInstance;
		}
		return *m_pInstance;
	}

	gvoid Initialize() {}

protected:
	GSingleton() {}
	~GSingleton() {}
	static LockT m_tLock;

private:
	GSingleton(const GSingleton<ClassT, LockT> &) {}
	GSingleton &operator=(const GSingleton<ClassT, LockT> &){ return *this; }

	static gvoid Destroy()
	{
		if (m_pInstance != GNULL)
			delete m_pInstance;
		m_pInstance = GNULL;
	}

	static ClassT * volatile m_pInstance;
};

template <typename ClassT, typename LockT>
ClassT *volatile GSingleton<ClassT, LockT>::m_pInstance = GNULL;

template <typename ClassT, typename LockT>
LockT GSingleton<ClassT, LockT>::m_tLock = LockT();

} // namespace gsystem

#endif // _CORE_SINGLETON_H_

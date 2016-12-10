/// 互斥量
#ifndef _CORE_MUTEX_H_
#define _CORE_MUTEX_H_

#include "CsLock.h"

class CS_API CsMutex final 
	: public CsLock
{
public:
	CsMutex();
	~CsMutex();
	cs_bool Lock();
	cs_bool Trylock();
	cs_void Unlock();

private:
	cs_bool Initialize();
	cs_void Release();
	cs_pointer m_pHandle;
};

#endif // _CORE_MUTEX_H_

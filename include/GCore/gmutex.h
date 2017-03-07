/// 互斥量
#ifndef _CORE_MUTEX_H_
#define _CORE_MUTEX_H_

#include "glock.h"

class GAPI GMutex final 
	: public GLock
{
public:
	GMutex();
	~GMutex();
	gvoid Lock();
	gbool Trylock();
	gvoid Unlock();

private:
	gbool Initialize();
	gvoid Release();

#ifdef G_SYSTEM_WINDOWS
	gpointer m_pHandle;
#endif // G_SYSTEM_WINDOWS
};

#endif // _CORE_MUTEX_H_

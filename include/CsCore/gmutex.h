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
	gbool Lock();
	gbool Trylock();
	gvoid Unlock();

private:
	gbool Initialize();
	gvoid Release();
	gpointer m_pHandle;
};

#endif // _CORE_MUTEX_H_

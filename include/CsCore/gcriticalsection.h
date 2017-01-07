/// ÁÙ½çÇø
#ifndef _CORE_CRITICAL_SECTION_H_
#define _CORE_CRITICAL_SECTION_H_

#include "glock.h"

class GAPI GCriticalSection final 
	: public GLock
{
public:
	GCriticalSection();
	~GCriticalSection();
	gbool Lock();
	gbool Trylock();
	gvoid Unlock();

private:
	gint Initialize();
	gvoid Release();
	gpointer m_pHandle;
};

#endif // _CORE_CRITICAL_SECTION_H_
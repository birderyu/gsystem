/// ÁÙ½çÇø
#ifndef _CORE_CRITICAL_SECTION_H_
#define _CORE_CRITICAL_SECTION_H_

#include "CsLock.h"

class CS_API CsCriticalSection final 
	: public CsLock
{
public:
	CsCriticalSection();
	~CsCriticalSection();
	cs_bool Lock();
	cs_bool Trylock();
	cs_void Unlock();

private:
	cs_int Initialize();
	cs_void Release();
	cs_pointer m_pHandle;
};

#endif // _CORE_CRITICAL_SECTION_H_
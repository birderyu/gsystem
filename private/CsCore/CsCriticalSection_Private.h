#ifndef _CORE_CRITICAL_SECTION_PRIVATE_H_
#define _CORE_CRITICAL_SECTION_PRIVATE_H_

#include "CsObject_Private.h"

class CsCriticalSection;

class CsCriticalSection_Private :public CsObject_Private
{
public:
	CsCriticalSection_Private(CsCriticalSection *pPublic);
	~CsCriticalSection_Private();
	cs_int Lock();
	cs_int TryLock();
	cs_void Unlock();

private:
	cs_int Initialize();
	cs_void Release();
	cs_pointer m_pHandle;
};

#endif // _CORE_CRITICAL_SECTION_PRIVATE_H_
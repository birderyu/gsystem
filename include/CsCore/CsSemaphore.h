#ifndef _CORE_SEMAPHORE_H_
#define _CORE_SEMAPHORE_H_

#include "CsGlobal.h"

/// 信号量
class CS_API CsSemaphore
{
public:
	CsSemaphore(cs_int nInitialValue = 1);
	~CsSemaphore();
	cs_int Wait();
	cs_int Wait(cs_ulong nMsecs);
	cs_void Post();

private:
	cs_int Initialize(cs_int nInitialValue);
	cs_pointer m_pHandle;
};

#endif // _CORE_SEMAPHORE_H_

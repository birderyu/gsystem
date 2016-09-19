#ifndef _CSCORE_CSSEMAPHORE_PRIVATE_H_
#define _CSCORE_CSSEMAPHORE_PRIVATE_H_

#include "CsObject_Private.h"

class CsSemaphore;

/// 信号量
class CsSemaphore_Private :public CsObject_Private
{
public:
	CsSemaphore_Private(CsSemaphore *pPublic, cs_int nInitialValue);
	~CsSemaphore_Private();
	cs_int Wait();
	cs_int Wait(cs_ulong nMsecs);
	cs_void Post();

private:
	cs_int Initialize(cs_int nInitialValue);
	cs_pointer m_pHandle;
};

#endif // _CSCORE_CSSEMAPHORE_PRIVATE_H_

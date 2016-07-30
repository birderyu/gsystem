#ifndef _CSCORE_CSSEMAPHORE_PRIVATE_H_
#define _CSCORE_CSSEMAPHORE_PRIVATE_H_

#include "CsObject_Private.h"

class CsSemaphore;

/// �ź���
class CsSemaphore_Private :public CsObject_Private
{
public:
	CsSemaphore_Private(CsSemaphore *pPublic, cs_int nInitialValue);
	~CsSemaphore_Private();
	cs_int Wait();
	cs_int Wait(cs_ulong nMsecs);
	void Post();

private:
	cs_int Initialize(cs_int nInitialValue);
	void *m_pHandle;
};

#endif // _CSCORE_CSSEMAPHORE_PRIVATE_H_

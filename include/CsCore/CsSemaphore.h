#ifndef _CSCORE_CSSEMAPHORE_H_
#define _CSCORE_CSSEMAPHORE_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

/// �ź���
class CsCore_Export CsSemaphore :public CsObject
{
public:
	CsSemaphore(cs_int nInitialValue = 1);
	~CsSemaphore();
	cs_int Wait();
	cs_int Wait(cs_ulong nMsecs);
	void Post();

public:
	enum { CLASSCODE = CORE_CLASSCODE_SEMAPHORE, };
};

#endif // _CSCORE_CSSEMAPHORE_H_

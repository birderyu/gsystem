#ifndef _CORE_SEMAPHORE_H_
#define _CORE_SEMAPHORE_H_

#include "gglobal.h"

/// 信号量
class GAPI GSemaphore
{
public:
	GSemaphore(gint nInitialValue = 1);
	~GSemaphore();
	gbool Wait();
	gbool Wait(gulong nMsecs);
	gvoid Post();

private:
	gint Initialize(gint nInitialValue);
	gpointer m_pHandle;
};

#endif // _CORE_SEMAPHORE_H_

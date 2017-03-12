#ifndef _CORE_SEMAPHORE_H_
#define _CORE_SEMAPHORE_H_

#include "gglobal.h"

namespace gnova { // gnova

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

} // namespace gnova

#endif // _CORE_SEMAPHORE_H_

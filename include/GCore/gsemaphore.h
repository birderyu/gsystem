#ifndef _CORE_SEMAPHORE_H_
#define _CORE_SEMAPHORE_H_

#include "gtype.h"

namespace gsystem { // gsystem

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
	gptr m_pHandle;
};

} // namespace gsystem

#endif // _CORE_SEMAPHORE_H_

#ifndef _CORE_SEMAPHORE_H_
#define _CORE_SEMAPHORE_H_

#include "gtype.h"

namespace gsystem { // gsystem

/// 信号量
class GAPI GSemaphore
{
public:
	GSemaphore(gint initialValue = 1);
	~GSemaphore();
	gbool Wait();
	gbool Wait(gulong msecs);
	gvoid Post();

private:
	gbool Initialize(gint initialValue);
	gptr m_pHandle;
};

} // namespace gsystem

#endif // _CORE_SEMAPHORE_H_

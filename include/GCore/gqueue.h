#ifndef _CORE_QUEUE_H_
#define _CORE_QUEUE_H_

#include "gobject.h"

namespace gsystem { // gsystem

template<typename DataT>
class GQueue
	: virtual public GObject
{
public:
	virtual ~GQueue() = 0;

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual gvoid Destroy() = 0;
	virtual gvoid Clear() = 0;

	// 入队
	virtual gvoid EnQueue(const DataT &data) = 0;
	virtual gvoid EnQueue(DataT &&data) = 0;

	// 出队
	virtual gvoid DeQueue(DataT *data = GNULL) = 0;

	virtual const DataT &Head() const = 0;
	virtual DataT &Head() = 0;
};

} // namespace gsystem

#include "inline/gqueue.inl"

#endif // _CORE_QUEUE_H_
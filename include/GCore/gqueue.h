#ifndef _CORE_QUEUE_H_
#define _CORE_QUEUE_H_

#include "gstructure.h"
#include "gobject.h"

namespace gsystem { // gsystem

template<typename DataT>
class GQueue
	: public GListT<GQueue<DataT>>
	, virtual public GObject
{
public:
	virtual ~GQueue() = 0;

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual gvoid Destroy() = 0;
	virtual gvoid Clear() = 0;

	// 入队
	virtual gbool EnQueue(const DataT &data) = 0;
	virtual gbool EnQueue(DataT &&data) = 0;

	// 出队
	virtual gbool DeQueue(DataT *data = GNULL) = 0;

	virtual const DataT &Head() const = 0; // 队首
	virtual DataT &Head() = 0; // 队首
	virtual const DataT &Tail() const = 0; // 队尾
	virtual DataT &Tail() = 0; // 队尾
};

} // namespace gsystem

#include "gqueue.inl"

#endif // _CORE_QUEUE_H_
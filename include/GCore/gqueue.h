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

	virtual gbool EnQueue(const DataT &data) = 0;
	virtual gbool EnQueue(DataT &&data) = 0;
	virtual gbool DeQueue(DataT *data = GNULL) = 0;

	virtual const DataT &Front() const = 0; // 队首
	virtual DataT &Front() = 0; // 队首
	virtual const DataT &Rear() const = 0; // 队尾
	virtual DataT &Rear() = 0; // 队尾
};

} // namespace gsystem

#include "gqueue.inl"

#endif // _CORE_QUEUE_H_
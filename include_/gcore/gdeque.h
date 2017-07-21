// 双端队列（Double-ended Queue）
#ifndef _CORE_DEQUE_H_
#define _CORE_DEQUE_H_

#include "gobject.h"

namespace gsystem { // gsystem

template<typename DataT>
class GDeque
	: virtual public GObject
{
public:
	virtual ~GDeque() = 0;

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual gvoid Destroy() = 0;
	virtual gvoid Clear() = 0;

	// 入队
	virtual gvoid PushBack(const DataT &data) = 0;
	virtual gvoid PushBack(DataT &&data) = 0;
	virtual gvoid PushFront(const DataT &data) = 0;
	virtual gvoid PushFront(DataT &&data) = 0;

	// 出队
	virtual gvoid PopBack(DataT *data = GNULL) = 0;
	virtual gvoid PopFront(DataT *data = GNULL) = 0;

	virtual DataT &First() = 0;
	virtual const DataT &First() const = 0;
	virtual DataT &Last() = 0;
	virtual const DataT &Last() const = 0;
};

} // namespace gsystem

#include "inline/gdeque.inl"

#endif // _CORE_DEQUE_H_
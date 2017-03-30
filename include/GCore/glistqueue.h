#ifndef _CORE_LIST_QUEUE_H_
#define _CORE_LIST_QUEUE_H_

#include "gqueue.h"
#include "gdoublelinkedlist.h"

namespace gsystem { // gsystem

template <typename DataT>
class GListQueue
	: public GQueue<DataT>
{
public:
	GListQueue();
	GListQueue(const GListQueue<DataT> &queue);
	GListQueue(GListQueue<DataT> &&queue);
	GListQueue<DataT>& operator=(const GListQueue<DataT> &queue);
	GListQueue<DataT>& operator=(GListQueue<DataT> &&queue);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Destroy();
	gvoid Clear();

	// 入队
	gvoid EnQueue(const DataT &data);
	gvoid EnQueue(DataT &&data);

	// 出队
	gvoid DeQueue(DataT *data = GNULL);

	const DataT &Head() const;
	DataT &Head();

private:
	GDoubleLinkedList<DataT> m_tList;
};

} // namespace gsystem

#include "glistqueue.inl"

#endif // _CORE_LIST_QUEUE_H_
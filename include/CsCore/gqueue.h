#ifndef _CORE_QUEUE_H_
#define _CORE_QUEUE_H_

#include "gobject.h"
#include "gstructure.h"

template<typename DataT>
class GQueue
	: public GListT<GQueue<DataT>>
	, public GObject
{
public:
	virtual ~GQueue() = 0 {}
	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual gvoid Clear() = 0;
	virtual gvoid Dispose() = 0;

	virtual gbool Push(const DataT& data) = 0;
	virtual gbool Pop(DataT *data = NULL) = 0;
	virtual gbool Top(DataT &data) const = 0;
};

#endif // _CORE_QUEUE_H_
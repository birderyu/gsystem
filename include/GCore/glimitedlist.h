// 受限制的线性表
#ifndef _CORE_LIMITED_LIST_H_
#define _CORE_LIMITED_LIST_H_

#include "gobject.h"
#include "gstructure.h"

template<typename DataT>
class GLimitedList
	: public GListT<GLimitedList<DataT>>
	, virtual public GObject
{
public:
	virtual ~GLimitedList() = 0 {}
	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;
	virtual gvoid Clear() = 0;
	virtual gvoid Dispose() = 0;

	virtual gbool Add(const DataT &data) = 0;
	virtual gbool Add(DataT &&data) = 0;
	virtual gbool Remove(DataT *data = GNULL) = 0;
};

#endif // _CORE_LIMITED_LIST_H_

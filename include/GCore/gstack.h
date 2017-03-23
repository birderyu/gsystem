#ifndef _CORE_STACK_H_
#define _CORE_STACK_H_

#include "gstructure.h"
#include "gobject.h"

namespace gsystem { // gsystem

template<typename DataT>
class GStack 
	: public GListT<GStack<DataT>>
	, virtual public GObject
{
public:
	virtual ~GStack() = 0;

	virtual gbool Push(const DataT &data) = 0;
	virtual gbool Push(DataT &&data) = 0;
	virtual gbool Pop(DataT *data = GNULL) = 0;

	virtual const DataT &Top() const = 0; // Õ»¶¥
	virtual DataT &Top() = 0; // Õ»¶¥
	virtual const DataT &Bottom() const = 0; // Õ»µ×
	virtual DataT &Bottom() = 0; // Õ»µ×
};

} // namespace gsystem

#include "gstack.inl"

#endif // _CORE_STACK_H_
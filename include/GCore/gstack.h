#ifndef _CORE_STACK_H_
#define _CORE_STACK_H_

#include "gobject.h"

namespace gsystem { // gsystem

template<typename DataT>
class GStack 
	: virtual public GObject
{
public:
	virtual ~GStack() = 0;

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual gvoid Destroy() = 0;
	virtual gvoid Clear() = 0;

	// »Î’ª
	virtual gvoid Push(const DataT &data) = 0;
	virtual gvoid Push(DataT &&data) = 0;

	// ≥ˆ’ª
	virtual gvoid Pop(DataT *data = GNULL) = 0;

	virtual const DataT &Top() const = 0; // ’ª∂•
	virtual DataT &Top() = 0; // ’ª∂•
};

} // namespace gsystem

#include "inline/gstack.inl"

#endif // _CORE_STACK_H_
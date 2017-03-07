#ifndef _CORE_STACK_H_
#define _CORE_STACK_H_

#include "glimitedlist.h"

// LIFO
template<typename DataT>
class GStack 
	: public GLimitedList<DataT>
{
public:
	virtual ~GStack() = 0;

	gbool Add(const DataT &data);
	gbool Add(DataT &&data);
	gbool Remove(DataT *data = GNULL);

	virtual gbool Push(const DataT &data) = 0;
	virtual gbool Push(DataT &&data) = 0;
	virtual gbool Pop(DataT *data = GNULL) = 0;

	virtual const DataT &Top() const = 0; // Õ»¶¥
	virtual DataT &Top() = 0; // Õ»¶¥
	virtual const DataT &Bottom() const = 0; // Õ»µ×
	virtual DataT &Bottom() = 0; // Õ»µ×
};

#include "gstack.inl"

#endif // _CORE_STACK_H_
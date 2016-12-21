#ifndef _CORE_STACK_H_
#define _CORE_STACK_H_

#include "CsObject.h"
#include "CsStructure.h"

template<typename DataT>
class CsStack 
	: public CsListT<CsStack<DataT>>
	, public CsObject
{
public:
	virtual ~CsStack() = 0 {}
	virtual cs_size_t Size() const = 0;
	virtual cs_bool IsEmpty() const = 0;

	virtual cs_void Clear() = 0;
	virtual cs_void Dispose() = 0;
	
	virtual cs_bool Push(const DataT& data) = 0;
	virtual cs_bool Pop(DataT *data = NULL) = 0;
	virtual cs_bool Top(DataT &data) const = 0;
};

#endif // _CORE_STACK_H_
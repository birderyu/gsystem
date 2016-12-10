#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "CsObject.h"

template <typename DataT>
class CsArray
	: public CsObject
{
public:
	virtual ~CsArray() = 0 {}

	virtual cs_size_t Size() const = 0;

	virtual DataT &GetAt(cs_size_t) = 0;
	virtual const DataT &GetAt(cs_size_t) const = 0;

	virtual DataT &operator[](cs_size_t) = 0;
	virtual const DataT &operator[](cs_size_t) const = 0;
};

#endif // _CORE_ARRAY_H_
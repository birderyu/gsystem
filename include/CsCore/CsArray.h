#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "CsObject.h"
#include "CsSerialize.h"
#include "CsStructure.h"

template <typename DataT>
class CsArray
	: public CsListT<CsArray<DataT>>
	, public CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_ARRAY, };

public:
	virtual ~CsArray() = 0 {}

	virtual cs_size_t Size() const = 0;
	virtual cs_bool IsEmpty() const = 0;

	virtual DataT &GetAt(cs_size_t) = 0;
	virtual const DataT &GetAt(cs_size_t) const = 0;

	virtual DataT &operator[](cs_size_t) = 0;
	virtual const DataT &operator[](cs_size_t) const = 0;

	virtual DataT *operator+=(cs_size_t) = 0;
	virtual const DataT *operator+=(cs_size_t) const = 0;

	cs_bool Contains(const DataT &) const;
	cs_size_t FirstIndexOf(const DataT &) const;
	cs_size_t LastIndexOf(const DataT &) const;
	cs_size_t CountOf(const DataT &) const;

	///
	virtual cs_uint ClassCode() const;
};

#include "CsArray.inl"

#endif // _CORE_ARRAY_H_
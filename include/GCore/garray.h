#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gobject.h"
#include "gserialize.h"
#include "gstructure.h"

template <typename DataT>
class GArray
	: public GListT<GArray<DataT>>
	, public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_ARRAY, };

public:
	virtual ~GArray() = 0 {}

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	virtual DataT &GetAt(gsize) = 0;
	virtual const DataT &GetAt(gsize) const = 0;

	virtual DataT &operator[](gsize) = 0;
	virtual const DataT &operator[](gsize) const = 0;

	virtual DataT *operator+=(gsize) = 0;
	virtual const DataT *operator+=(gsize) const = 0;

	gbool Contains(const DataT &) const;
	gsize FirstIndexOf(const DataT &) const;
	gsize LastIndexOf(const DataT &) const;
	gsize CountOf(const DataT &) const;

	///
	virtual guint ClassCode() const;
};

#include "garray.inl"

#endif // _CORE_ARRAY_H_
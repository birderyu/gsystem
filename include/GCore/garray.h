#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gstructure.h"
#include "gobject.h"

namespace gsystem { // gsystem

template <typename DataT>
class GArray
	: public GListT<GArray<DataT>>
	, virtual public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_ARRAY, };

public:
	virtual ~GArray() = 0 {}

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	//virtual DataT &ConstGetAt(gsize pos) const = 0;
	virtual DataT &GetAt(gsize pos) = 0;
	virtual const DataT &GetAt(gsize pos) const = 0;

	//virtual DataT *ConstCursorAt(gsize pos) const = 0;
	virtual DataT *CursorAt(gsize pos) = 0;
	virtual const DataT *CursorAt(gsize pos) const = 0;

	virtual DataT &operator[](gsize pos) = 0;
	virtual const DataT &operator[](gsize pos) const = 0;

	gbool Contains(const DataT &) const;
	gsize FirstIndexOf(const DataT &) const;
	gsize LastIndexOf(const DataT &) const;
	gsize CountOf(const DataT &) const;

	///
	virtual guint ClassCode() const;
};

} // namespace gsystem

#include "garray.inl"

#endif // _CORE_ARRAY_H_
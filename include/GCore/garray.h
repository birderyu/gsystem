#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gstruct.h"
#include "gobject.h"

namespace gsystem { // gsystem

template <typename DataT>
class GArray
	: public GListT<GArray<DataT>>
	, virtual public GObject
{
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

	DataT &First();
	const DataT &First() const;
	DataT &Last();
	const DataT &Last() const;

	DataT *FirstCursor();
	const DataT *FirstCursor() const;
	DataT *LastCursor();
	const DataT *LastCursor() const;

	gbool Contains(const DataT &) const;
	gsize FirstIndexOf(const DataT &) const;
	gsize LastIndexOf(const DataT &) const;
	gsize CountOf(const DataT &) const;
};

} // namespace gsystem

#include "inline/garray.inl"

#endif // _CORE_ARRAY_H_
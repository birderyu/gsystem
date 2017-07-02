/// ¾²Ì¬Êý×é
#ifndef _CORE_STATIC_ARRAY_H_
#define _CORE_STATIC_ARRAY_H_

#include "garray.h"

namespace gsystem { // gsystem

template <typename DataT, gsize ARRAY_SIZE>
class GStaticArray final
	: public GArray<DataT>
{
public:
	GStaticArray();
	GStaticArray(const DataT &);

	gsize Size() const;
	gbool IsEmpty() const;

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

	DataT *operator+=(gsize);
	const DataT *operator+=(gsize) const;

private:
	DataT m_pData[ARRAY_SIZE];
};

} // namespace gsystem

#include "inline/gstaticarray.inl"

#endif // _CORE_STATIC_ARRAY_H_
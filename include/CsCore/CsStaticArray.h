/// ¾²Ì¬Êý×é

#ifndef _CORE_STATIC_ARRAY_H_
#define _CORE_STATIC_ARRAY_H_

#include "CsArray.h"

template <typename DataT, cs_size_t ARRAY_SIZE>
class CsStaticArray
	: public CsArray<DataT>
{
public:
	CsStaticArray();
	CsStaticArray(const DataT &);

	cs_size_t Size() const;

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;

private:
	DataT m_pData[ARRAY_SIZE];
};

#include "CsStaticArray.inl"

#endif // _CORE_STATIC_ARRAY_H_
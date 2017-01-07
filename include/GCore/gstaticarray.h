/// ¾²Ì¬Êý×é
#ifndef _CORE_STATIC_ARRAY_H_
#define _CORE_STATIC_ARRAY_H_

#include "garray.h"

template <typename DataT, gsize ARRAY_SIZE>
class GStaticArray final
	: public GArray<DataT>
{
public:
	enum { CLASS_CODE = CLASS_CODE_STATIC_ARRAY, };

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

	/// 
	guint ClassCode() const;
	gbool Serializable() const;
	template<typename ArchiveT> gbool Serialize(ArchiveT &) const;
	template<typename ArchiveT> gbool Deserialize(ArchiveT &);

private:
	DataT m_pData[ARRAY_SIZE];
};

#include "gstaticarray.inl"

#endif // _CORE_STATIC_ARRAY_H_
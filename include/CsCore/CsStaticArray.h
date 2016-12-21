/// ¾²Ì¬Êý×é

#ifndef _CORE_STATIC_ARRAY_H_
#define _CORE_STATIC_ARRAY_H_

#include "CsArray.h"

template <typename DataT, cs_size_t ARRAY_SIZE>
class CsStaticArray final
	: public CsArray<DataT>
{
public:
	enum { CLASS_CODE = CLASS_CODE_STATIC_ARRAY, };

public:
	CsStaticArray();
	CsStaticArray(const DataT &);

	cs_size_t Size() const;

	DataT &GetAt(cs_size_t);
	DataT  GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	DataT  operator[](cs_size_t) const;

	/// 
	cs_uint ClassCode() const;
	cs_bool Serializable() const;
	template<typename ArchiveT> cs_bool Serialize(ArchiveT &) const;
	template<typename ArchiveT> cs_bool Deserialize(ArchiveT &);

private:
	DataT m_pData[ARRAY_SIZE];
};

#include "CsStaticArray.inl"

#endif // _CORE_STATIC_ARRAY_H_
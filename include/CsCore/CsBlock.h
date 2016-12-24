#ifndef _CORE_BLOCK_H_
#define _CORE_BLOCK_H_

#include "CsGlobal.h"
#include "CsNew.h"
#include "CsStructure.h"

template<typename DataT>
class CsBlock
	: public CsListT<CsBlock<DataT>>
{
public:
	// 单位：字节
	CsBlock(cs_size_t nSize = 0);
	CsBlock(const CsBlock<DataT> &);
	~CsBlock();

	cs_bool Valid() const;
	cs_size_t Size() const;	// 内存总长度
	DataT *Cursor(cs_size_t nCursor) const;

	cs_bool Resize(cs_size_t nSize);
	cs_bool Resize(cs_size_t nSize, cs_size_t nStart, cs_size_t nLength);

	cs_bool CreateFrom(const CsBlock<DataT> &tFrom);
	cs_bool CreateFrom(const CsBlock<DataT> &tFrom, cs_size_t nFromStart, cs_size_t nFromLength);

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;

private:
	// Not Safe
	CsBlock(DataT *, cs_size_t, cs_bool bAutoRelease = false);

	cs_bool Initialize();
	cs_void Free();

	DataT *m_pMemory;
	cs_size_t m_nSize;
	cs_bool m_bAutoRelease;
};

#include "CsBlock.inl"

#endif // _CORE_BLOCK_H_
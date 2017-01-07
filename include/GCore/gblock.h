#ifndef _CORE_BLOCK_H_
#define _CORE_BLOCK_H_

#include "gglobal.h"
#include "gnew.h"
#include "gstructure.h"

template<typename DataT>
class GBlock
	: public GListT<GBlock<DataT>>
{
public:
	// 单位：字节
	GBlock(gsize nSize = 0);
	GBlock(const GBlock<DataT> &);
	~GBlock();

	gbool Valid() const;
	gsize Size() const;	// 内存总长度
	DataT *Cursor(gsize nCursor) const;

	gbool Resize(gsize nSize);
	gbool Resize(gsize nSize, gsize nStart, gsize nLength);

	gbool CreateFrom(const GBlock<DataT> &tFrom);
	gbool CreateFrom(const GBlock<DataT> &tFrom, gsize nFromStart, gsize nFromLength);

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

private:
	// Not Safe
	GBlock(DataT *, gsize, gbool bAutoRelease = false);

	gbool Initialize();
	gvoid Free();

	DataT *m_pMemory;
	gsize m_nSize;
	gbool m_bAutoRelease;
};

#include "gblock.inl"

#endif // _CORE_BLOCK_H_
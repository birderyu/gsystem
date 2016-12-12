/// 内存块

#ifndef _CORE_BLOCK_H_
#define _CORE_BLOCK_H_

#include "CsGlobal.h"

class CS_API CsBlock
{
public:
	// 单位：字节
	CsBlock(cs_size_t nSize = 0);
	CsBlock(const CsBlock &);
	~CsBlock();

	cs_bool Valid() const;
	cs_size_t Size() const;	// 内存总长度
	cs_pointer Cursor(cs_size_t nCursor) const;

	cs_bool Resize(cs_size_t nSize);
	cs_bool Resize(cs_size_t nSize, cs_size_t nStart, cs_size_t nLength);

	cs_bool CreateFrom(const CsBlock &tFrom);
	cs_bool CreateFrom(const CsBlock &tFrom, cs_size_t nFromStart, cs_size_t nFromLength);

private:
	// Not Safe
	CsBlock(cs_pointer, cs_size_t, cs_bool bAutoRelease = false);

	cs_bool Initialize();
	cs_void Free();

	cs_pointer m_pMemory;
	cs_size_t m_nMemSize;
	cs_bool m_bAutoRelease;
};

#endif // _CORE_BLOCK_H_
// GBlock是一个byte数组
// 当Block无法分配内存时，会跑出一个异常

#ifndef _CORE_BLOCK_H_
#define _CORE_BLOCK_H_

#include "gglobal.h"
#include "gstructure.h"

class GAPI GBlock
	: public GListT<GBlock>
{
public:
	// 单位：字节
	GBlock(gsize nSize = 0);
	GBlock(const GBlock &);
	GBlock(GBlock &&);
	~GBlock();
	
	gsize Size() const;	// 内存总长度
	gbyte *CursorAt(gsize nCursor);
	const gbyte *CursorAt(gsize nCursor) const;

	gvoid Resize(gsize nSize);

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;

	gbyte &operator[](gsize);
	const gbyte &operator[](gsize) const;

private:
	// Not Safe
	GBlock(gbyte *, gsize, gbool bAutoRelease = false);

	gbool Valid() const;

	gvoid Initialize();
	gvoid Free();

	// 数组的长度
	gsize m_nSize;

	// 第一位存储AutoRelease
	// 第二位存储是否是指针类型：0，非指针；1，指针
	gbyte m_tConfig[2];

	union
	{
		gbyte m_tBlock[G_POINTER_ADDRESS_SIZE];
		gbyte *m_pBlock;
	};
};

#endif // _CORE_BLOCK_H_
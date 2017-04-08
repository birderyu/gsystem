// 引用计数器
#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gnew.h"

namespace gsystem { // gsystem

template <typename ClassT>
class GRefCounter 
	: public GNewT<GRefCounter<ClassT>>
{
public:
	// count: 初始引用计数，默认为1
	GRefCounter(ClassT *ptr, gsize count = 1);
	~GRefCounter();
	gsize Add();
	gvoid Release();
	gsize Count() const;
	ClassT *Pointer();
	const ClassT *Pointer() const;

private:
	gsize m_nCount;
	ClassT *m_pPointer;
};

} // namespace gsystem

#include "grefcounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_
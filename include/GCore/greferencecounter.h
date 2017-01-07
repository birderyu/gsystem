// 引用计数器
#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gatomic.h"
#include "gnew.h"

template <typename ClassT, typename LockT = GMutex>
class GReferenceCounter 
	: public GNewT<GReferenceCounter<ClassT, LockT>>
{
public:
	// count: 初始引用计数，默认为1
	GReferenceCounter(ClassT *ptr, gsize count = 1);
	virtual ~GReferenceCounter();
	gsize Add();
	gvoid Release();
	gsize Count() const;
	ClassT *Pointer();
	const ClassT *Pointer() const;

private:
	GAtomic<gsize, LockT> m_nCount;
	ClassT *m_pPointer;
};

#include "greferencecounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_
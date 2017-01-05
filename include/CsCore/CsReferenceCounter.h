// 引用计数器
#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "CsAtomic.h"
#include "CsNew.h"

template <typename ClassT, typename LockT = CsMutex>
class CsReferenceCounter 
	: public CsNewT<CsReferenceCounter<ClassT, LockT>>
{
public:
	// count: 初始引用计数，默认为1
	CsReferenceCounter(ClassT *ptr, cs_size_t count = 1);
	virtual ~CsReferenceCounter();
	cs_size_t Add();
	cs_void Release();
	cs_size_t Count() const;
	ClassT *Pointer();
	const ClassT *Pointer() const;

private:
	CsAtomic<cs_size_t, LockT> m_nCount;
	ClassT *m_pPointer;
};

#include "CsReferenceCounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_
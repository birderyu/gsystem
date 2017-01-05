#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "CsReferenceCounter.h"

template <typename ClassT, typename LockT = CsMutex>
class CsSharedPointer
{
public:
	// count: 初始引用计数，默认为1
	CsSharedPointer(ClassT *ptr = NULL, cs_size_t count = 1);
	CsSharedPointer(const CsSharedPointer<ClassT, LockT> &);
	~CsSharedPointer();

	// 重置指针
	cs_void Reset(ClassT *);

	// 指针是否为NULL
	cs_bool IsNull() const;

	// 指针是否被共享
	cs_bool IsShared() const;

	// 引用计数器操作
	cs_size_t Add();
	cs_void Release();
	cs_size_t Count() const;

	CsSharedPointer<ClassT, LockT> &operator=(const CsSharedPointer<ClassT, LockT> &);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator&();
	const ClassT *operator&() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	CsReferenceCounter<ClassT, LockT> *m_pRefCounter;
};

#include "CsSharedPointer.inl"

#endif // _CORE_SHARED_POINTER_H_
#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "greferencecounter.h"

template <typename ClassT, typename LockT = GMutex>
class GSharedPointer
{
public:
	// count: 初始引用计数，默认为1
	GSharedPointer(ClassT *ptr = NULL, gsize count = 1);
	GSharedPointer(const GSharedPointer<ClassT, LockT> &);
	~GSharedPointer();

	// 重置指针
	gvoid Reset(ClassT *);

	// 指针是否为NULL
	gbool IsNull() const;

	// 指针是否被共享
	gbool IsShared() const;

	// 引用计数器操作
	gsize Add();
	gvoid Release();
	gsize Count() const;

	GSharedPointer<ClassT, LockT> &operator=(const GSharedPointer<ClassT, LockT> &);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator&();
	const ClassT *operator&() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	GReferenceCounter<ClassT, LockT> *m_pRefCounter;
};

#include "gsharedpointer.inl"

#endif // _CORE_SHARED_POINTER_H_
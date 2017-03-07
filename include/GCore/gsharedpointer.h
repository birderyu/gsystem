#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "greferencecounter.h"

template <typename ClassT>
class GSharedPointer
{
public:
	// count: 初始引用计数，默认为1
	GSharedPointer(ClassT *ptr = GNULL, gsize count = 1);
	GSharedPointer(const GSharedPointer<ClassT> &ptr);
	GSharedPointer(GSharedPointer<ClassT> &&ptr);
	~GSharedPointer();

	// 重置指针
	gvoid Reset(ClassT *ptr, gsize count = 1);

	// 指针是否被共享
	gbool Shared() const;

	// 动态转换
	template<typename NexClassT>
	GSharedPointer<NexClassT> DynamicConvertTo();

	operator gbool() const;
	GSharedPointer<ClassT> &operator=(const GSharedPointer<ClassT> &);
	GSharedPointer<ClassT> &operator=(GSharedPointer<ClassT> &&);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	GReferenceCounter<ClassT> *m_pRefCounter;
};

template<typename ClassT, typename... TS> GSharedPointer<ClassT> GMakeShared(TS&&... args);

#include "gsharedpointer.inl"

#endif // _CORE_SHARED_POINTER_H_
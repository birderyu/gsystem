#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "grefcounter.h"

namespace gsystem { // gsystem

template <typename ClassT>
class GSharedPtr
{
public:
	// count: 初始引用计数，默认为1
	GSharedPtr(ClassT *ptr = GNULL, gsize count = 1);
	GSharedPtr(const GSharedPtr<ClassT> &ptr);
	GSharedPtr(GSharedPtr<ClassT> &&ptr);
	~GSharedPtr();

	// 重置指针
	gvoid Reset(ClassT *ptr, gsize count = 1);

	// 指针是否被共享
	gbool Shared() const;

	// 动态转换
	template<typename NexClassT>
	GSharedPtr<NexClassT> DynamicConvertTo();

	operator gbool() const;
	GSharedPtr<ClassT> &operator=(const GSharedPtr<ClassT> &);
	GSharedPtr<ClassT> &operator=(GSharedPtr<ClassT> &&);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	GRefCounter<ClassT> *m_pRefCounter;
};

template<typename ClassT, typename... TS> GSharedPtr<ClassT> GMakeShared(TS&&... args);

} // namespace gsystem

#include "inline/gsharedptr.inl"

#endif // _CORE_SHARED_POINTER_H_
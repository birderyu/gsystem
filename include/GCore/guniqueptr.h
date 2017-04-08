#ifndef _CORE_UNIQUE_POINTER_H_
#define _CORE_UNIQUE_POINTER_H_

#include "gtype.h"
#include "gnocopyable.h"

namespace gsystem { // gsystem

template <typename ClassT>
class GUniquePtr
	: private GNocopyable
{
public:
	GUniquePtr(ClassT *ptr = GNULL);
	GUniquePtr(GUniquePtr<ClassT> &&ptr);
	~GUniquePtr();
	gvoid Reset(ClassT *);
	ClassT *Release();

	operator gbool() const;
	GUniquePtr<ClassT> &operator=(GUniquePtr<ClassT> &&ptr);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator->();
	const ClassT *operator->() const;

private:
	ClassT *m_pPointer;
};

template<typename ClassT, typename... TS> GUniquePtr<ClassT> GMakeUnique(TS&&... args);

} // namespace gsystem

#include "guniqueptr.inl"

#endif // _CORE_UNIQUE_POINTER_H_
#ifndef _CORE_UNIQUE_POINTER_H_
#define _CORE_UNIQUE_POINTER_H_

#include "gglobal.h"
#include "gnocopyable.h"

namespace gnova { // gnova

template <typename ClassT>
class GUniquePointer
	: private GNocopyable
{
public:
	GUniquePointer(ClassT *ptr = GNULL);
	GUniquePointer(GUniquePointer<ClassT> &&ptr);
	~GUniquePointer();
	gvoid Reset(ClassT *);
	ClassT *Release();

	operator gbool() const;
	GUniquePointer<ClassT> &operator=(GUniquePointer<ClassT> &&ptr);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator->();
	const ClassT *operator->() const;

private:
	ClassT *m_pPointer;
};

template<typename ClassT, typename... TS> GUniquePointer<ClassT> GMakeUnique(TS&&... args);

} // namespace gnova

#include "guniquepointer.inl"

#endif // _CORE_UNIQUE_POINTER_H_
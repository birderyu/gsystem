#ifndef _CORE_POINTER_ARRAY_H
#define _CORE_POINTER_ARRAY_H

#include "CsDynamicArray.h"

template <typename T, cs_bool auto_release = false>
class CsPointerArray
{
public:
	CsPointerArray();

private:
	CsDynamicArray<T*> m_tPtrArray;
};

#endif // _CORE_POINTER_ARRAY_H
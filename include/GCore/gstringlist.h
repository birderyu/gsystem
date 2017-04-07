#ifndef _CORE_STRING_LIST_H_
#define _CORE_STRING_LIST_H_

#include "gstring.h"
#include "gvector.h"

namespace gsystem { // gsystem

class GAPI GStringList
{
public:
	gsize Size() const;
	gbool IsEmpty() const;

	GString &GetAt(gsize pos);
	const GString &GetAt(gsize pos) const;

	gvoid Add(const GString &str);
	gvoid Add(GString &&str);
	gvoid SetAt(gsize pos, const GString &str);

private:
	GDynamicArray<GString> m_tStrings;
};

} // namespace gsystem

#endif // _CORE_STRING_LIST_H_
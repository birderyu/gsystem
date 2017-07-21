#ifndef _CORE_STRING_LIST_H_
#define _CORE_STRING_LIST_H_

#include "gvector.h"

namespace gsystem { // gsystem

template <typename StringT>
class GStringListT final
	: public GArray<StringT>
	, public GSerializable
{
	static_assert(GIsSame<StringT, GString8>::value 
		|| GIsSame<StringT, GString16>::value
		|| GIsSame<StringT, GString32>::value,
		"string type of GStringListT must by GString8 or GString16 or GString32.");

public:
	GStringListT();
	GStringListT(const GStringListT<StringT> &strList);
	GStringListT(GStringListT<StringT> &&strList);
	GStringListT<StringT> &operator=(const GStringListT<StringT> &strList);
	GStringListT<StringT> &operator=(GStringListT<StringT> &&strList);

public:
	gsize Size() const;
	gbool IsEmpty() const;

	StringT &GetAt(gsize pos);
	const StringT &GetAt(gsize pos) const;
	StringT &operator[](gsize pos);
	const StringT &operator[](gsize pos) const;

	StringT *CursorAt(gsize pos);
	const StringT *CursorAt(gsize pos) const;

	gvoid Add(const StringT &str);
	gvoid Add(StringT &&str);
	gvoid SetAt(gsize pos, const StringT &str);
	gvoid RemoveAt(gsize pos);

public:
	guint ClassCode() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	GVector<StringT> m_tStrings;
};

} // namespace gsystem

#include "inline/gstringlist.inl"

#endif // _CORE_STRING_LIST_H_
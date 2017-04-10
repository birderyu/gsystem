#ifndef _CORE_STRING_LIST_H_
#define _CORE_STRING_LIST_H_

#include "gstring.h"
#include "gvector.h"

namespace gsystem { // gsystem

class GAPI GStringList
	: public GArray<GString>
	, virtual public GObject
	, virtual public GSerializable
{
public:
	GStringList();
	GStringList(const GStringList &strList);
	GStringList(GStringList &&strList);
	GStringList &operator=(const GStringList &strList);
	GStringList &operator=(GStringList &&strList);

public:
	gsize Size() const;
	gbool IsEmpty() const;

	GString &GetAt(gsize pos);
	const GString &GetAt(gsize pos) const;
	GString &operator[](gsize pos);
	const GString &operator[](gsize pos) const;

	GString *CursorAt(gsize pos);
	const GString *CursorAt(gsize pos) const;

	gvoid Add(const GString &str);
	gvoid Add(GString &&str);
	gvoid SetAt(gsize pos, const GString &str);
	gvoid RemoveAt(gsize pos);

public:
	guint ClassCode() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	GVector<GString> m_tStrings;
};

} // namespace gsystem

#endif // _CORE_STRING_LIST_H_
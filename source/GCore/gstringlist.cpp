#include "gstringlist.h"

namespace gsystem { // gsystem

gsize GStringList::Size() const
{
	//return m_tStrings.Size();
	return 0;
}

gbool GStringList::IsEmpty() const
{
	//return m_tStrings.IsEmpty();
	return true;
}

GString &GStringList::GetAt(gsize pos)
{
	//return m_tStrings.GetAt(pos);
	return GString();
}

const GString &GStringList::GetAt(gsize pos) const
{
	//return m_tStrings.GetAt(pos);
	return GString();
}

gvoid GStringList::Add(const GString &str)
{
	//return m_tStrings.PushBack(str);
}

gvoid GStringList::Add(GString &&str)
{
	//return m_tStrings.PushBack(GForward<GString>(str));
}

gvoid GStringList::SetAt(gsize pos, const GString &str)
{
	//m_tStrings[pos] = str;
}

} // namespace gsystem

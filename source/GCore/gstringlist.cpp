#include "gstringlist.h"

namespace gsystem { // gsystem

GStringList::GStringList()
{

}

GStringList::GStringList(const GStringList &strList)
	: m_tStrings(strList.m_tStrings)
{

}

GStringList::GStringList(GStringList &&strList)
	: m_tStrings(GMove(strList.m_tStrings))
{

}

GStringList &GStringList::operator=(const GStringList &strList)
{
	if (this == &strList)
	{
		return *this;
	}
	m_tStrings = strList.m_tStrings;
	return *this;
}

GStringList &GStringList::operator=(GStringList &&strList)
{
	if (this == &strList)
	{
		return *this;
	}
	m_tStrings = GMove(strList.m_tStrings);
	return *this;
}

gsize GStringList::Size() const
{
	return m_tStrings.Size();
}

gbool GStringList::IsEmpty() const
{
	return m_tStrings.IsEmpty();
}

GString &GStringList::GetAt(gsize pos)
{
	return m_tStrings.GetAt(pos);
}

const GString &GStringList::GetAt(gsize pos) const
{
	return m_tStrings.GetAt(pos);
}

GString &GStringList::operator[](gsize pos)
{
	return m_tStrings[pos];
}

const GString &GStringList::operator[](gsize pos) const
{
	return m_tStrings[pos];
}

GString *GStringList::CursorAt(gsize pos)
{
	return m_tStrings.CursorAt(pos);
}

const GString *GStringList::CursorAt(gsize pos) const
{
	return m_tStrings.CursorAt(pos);
}

gvoid GStringList::Add(const GString &str)
{
	m_tStrings.PushBack(str);
}

gvoid GStringList::Add(GString &&str)
{
	m_tStrings.PushBack(GForward<GString>(str));
}

gvoid GStringList::SetAt(gsize pos, const GString &str)
{
	m_tStrings[pos] = str;
}

gvoid GStringList::RemoveAt(gsize pos)
{
	m_tStrings.RemoveAt(pos);
}

guint GStringList::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::StringList);
}

gbool GStringList::Serialize(GArchive &archive) const
{
	return false;
}

gbool GStringList::Deserialize(GArchive &archive)
{
	return false;
}

} // namespace gsystem

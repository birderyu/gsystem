#include "gstringlist.h"
#include "gstring.h"
#include "gcstringhelper.h"

GString GStringList::GetAt(gsize pos, G_STRING_TYPE emStrType) const
{
	if (emStrType == STRING_TYPE_VALUE)
	{
		return GString((gchar*)(m_t.Find(pos).Value()));
	}
	else
	{
		// STRING_TYPE_REFERENCE
		// TODO
	}
	return GString();
}

gbool GStringList::Add(const GString &str)
{
	if (str.IsEmpty())
	{
		return false;
	}
	gchar *ptr = (gchar*)m_tPool.Alloc(str.Size() + 1);
	if (!ptr)
	{
		return false;
	}
	GCStringHelper::Copy(str.CString(), str.Size() + 1, ptr);
	m_t.Insert(m_t.Size(), ptr);
	return true;
}

gsize GStringList::Size() const
{
	return 0;
}

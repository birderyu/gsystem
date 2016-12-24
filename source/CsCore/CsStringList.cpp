#include "CsStringList.h"
#include "CsString.h"
#include "CsCStringHelper.h"

CsString CsStringList::GetAt(cs_size_t id, CS_STRING_TYPE emStrType) const
{
	if (emStrType == STRING_TYPE_VALUE)
	{
		return CsString((cs_char*)(m_t.find(id)->second));
	}
	else
	{
		// STRING_TYPE_REFERENCE
		// TODO
	}
	return CsString();
}

cs_bool CsStringList::Add(const CsString &str)
{
	if (str.IsEmpty())
	{
		return false;
	}
	cs_char *ptr = (cs_char*)m_tPool.Alloc(str.Size() + 1);
	if (!ptr)
	{
		return false;
	}
	CsCStringHelper::Copy(str.CString(), str.Size() + 1, ptr);
	m_t.insert(std::pair<cs_size_t, cs_pointer>(m_t.size(), ptr));
	return true;
}

cs_size_t CsStringList::Size() const
{
	return 0;
}

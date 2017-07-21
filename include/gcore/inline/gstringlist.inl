#ifndef _CORE_STRING_LIST_INLINE_
#define _CORE_STRING_LIST_INLINE_

namespace gsystem { // gsystem

template <typename StringT>
GStringListT<StringT>::GStringListT()
{

}

template <typename StringT>
GStringListT<StringT>::GStringListT(const GStringListT<StringT> &strList)
	: m_tStrings(strList.m_tStrings)
{

}

template <typename StringT>
GStringListT<StringT>::GStringListT(GStringListT<StringT> &&strList)
	: m_tStrings(GMove(strList.m_tStrings))
{

}

template <typename StringT>
GStringListT<StringT> &GStringListT<StringT>::operator=(const GStringListT<StringT> &strList)
{
	if (this == &strList)
	{
		return *this;
	}
	m_tStrings = strList.m_tStrings;
	return *this;
}

template <typename StringT>
GStringListT<StringT> &GStringListT<StringT>::operator=(GStringListT<StringT> &&strList)
{
	if (this == &strList)
	{
		return *this;
	}
	m_tStrings = GMove(strList.m_tStrings);
	return *this;
}

template <typename StringT>
gsize GStringListT<StringT>::Size() const
{
	return m_tStrings.Size();
}

template <typename StringT>
gbool GStringListT<StringT>::IsEmpty() const
{
	return m_tStrings.IsEmpty();
}

template <typename StringT>
StringT &GStringListT<StringT>::GetAt(gsize pos)
{
	return m_tStrings.GetAt(pos);
}

template <typename StringT>
const StringT &GStringListT<StringT>::GetAt(gsize pos) const
{
	return m_tStrings.GetAt(pos);
}

template <typename StringT>
StringT &GStringListT<StringT>::operator[](gsize pos)
{
	return m_tStrings[pos];
}

template <typename StringT>
const StringT &GStringListT<StringT>::operator[](gsize pos) const
{
	return m_tStrings[pos];
}

template <typename StringT>
StringT *GStringListT<StringT>::CursorAt(gsize pos)
{
	return m_tStrings.CursorAt(pos);
}

template <typename StringT>
const StringT *GStringListT<StringT>::CursorAt(gsize pos) const
{
	return m_tStrings.CursorAt(pos);
}

template <typename StringT>
gvoid GStringListT<StringT>::Add(const StringT &str)
{
	m_tStrings.PushBack(str);
}

template <typename StringT>
gvoid GStringListT<StringT>::Add(StringT &&str)
{
	m_tStrings.PushBack(GForward<StringT>(str));
}

template <typename StringT>
gvoid GStringListT<StringT>::SetAt(gsize pos, const StringT &str)
{
	m_tStrings[pos] = str;
}

template <typename StringT>
gvoid GStringListT<StringT>::RemoveAt(gsize pos)
{
	m_tStrings.RemoveAt(pos);
}

template <typename StringT>
guint GStringListT<StringT>::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::StringList);
}

template <typename StringT>
gbool GStringListT<StringT>::Serialize(GArchive &archive) const
{
	// TODO
	return false;
}

template <typename StringT>
gbool GStringListT<StringT>::Deserialize(GArchive &archive)
{
	// TODO
	return false;
}

} // namespace gsystem

#endif // _CORE_STRING_LIST_INLINE_
#ifndef _CORE_BASE_STRING_INLINE_
#define _CORE_BASE_STRING_INLINE_

namespace gsystem {

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString()
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(CharT c)
	: m_tString(1)
{
	m_tString.Resize(1);
	m_tString[0] = c;
}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(typname GBaseString<CharT>::CStringT str)
{
	gsize size = GCString::Size(str);
	m_tString.Resize(size);
	GCString::Copy(str, size, m_tString.Start());
}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(typname GBaseString<CharT>::CStringT str, gsize size)
	: m_tString(str, size)
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(const typname GBaseString<CharT>::StringDataT &str)
	: m_tString(str)
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(typname GBaseString<CharT>::StringDataT &&str)
	: m_tString(GForward<typname GBaseString<CharT>::StringDataT>(str))
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(const GBaseString<CharT> &str)
	: m_tString(str.m_tString)
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(GBaseString<CharT> &&str)
	: m_tString(GMove(str.m_tString))
{

}


template<typename CharT> GINLINE
GBaseString<CharT>::~GBaseString()
{

}

template<typename CharT> GINLINE
gsize GBaseString<CharT>::Size() const
{
	return m_tString.Size();
}

template<typename CharT> GINLINE
gsize GBaseString<CharT>::Length() const
{
	// TODO
	return m_tString.Size();
}

template<typename CharT> GINLINE
gbool GBaseString<CharT>::IsEmpty() const
{
	return m_tString.IsEmpty();
}

template<typename CharT> GINLINE
CharT &GBaseString<CharT>::GetAt(gsize pos)
{
	return m_tString.GetAt(pos);
}

template<typename CharT> GINLINE
const CharT &GBaseString<CharT>::GetAt(gsize pos) const
{
	return m_tString.GetAt(pos);
}

template<typename CharT> GINLINE
CharT *GBaseString<CharT>::CursorAt(gsize)
{
	return m_tString.CursorAt(pos);
}

template<typename CharT> GINLINE
const CharT *GBaseString<CharT>::CursorAt(gsize) const
{
	return m_tString.CursorAt(pos);
}

template<typename CharT> GINLINE
gvoid GBaseString<CharT>::Resize(gsize size)
{
	m_tString.Resize(size);
}

template<typename CharT> GINLINE
gvoid GBaseString<CharT>::Reserve(gsize size)
{
	m_tString.Reserve(capacity);
}

template<typename CharT> GINLINE
gbool GBaseString<CharT>::StartWith(CharT c) const
{
	if (IsEmpty())
	{
		return false;
	}
	return GetAt[0] == c;
}

template<typename CharT> GINLINE
gbool GBaseString<CharT>::EndWith(CharT c) const
{
	if (IsEmpty())
	{
		return false;
	}
	return GetAt(Size() - 1) == c;
}

}

#endif // _CORE_BASE_STRING_INLINE_
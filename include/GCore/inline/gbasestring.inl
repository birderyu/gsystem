#ifndef _CORE_BASE_STRING_INLINE_
#define _CORE_BASE_STRING_INLINE_

#include "gcstring.h"

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
GBaseString<CharT>::GBaseString(typename GBaseString<CharT>::CStringT str)
{
	gsize size = GCString::Size(str);
	m_tString.Resize(size);
	GCString::Copy(str, size, m_tString.Start());
}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(typename GBaseString<CharT>::CStringT str, gsize size)
	: m_tString(str, size)
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(const typename GBaseString<CharT>::StringDataT &str)
	: m_tString(str)
{

}

template<typename CharT> GINLINE
GBaseString<CharT>::GBaseString(typename GBaseString<CharT>::StringDataT &&str)
	: m_tString(GForward<typename GBaseString<CharT>::StringDataT>(str))
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
typename GBaseString<CharT>::CStringT GBaseString<CharT>::CString() const
{
	return m_tString.Start();
}

template<typename CharT> GINLINE
gsize GBaseString<CharT>::Size() const
{
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

template<typename CharT> GINLINE
gvoid GBaseString<CharT>::Append(const GBaseString<CharT> &str)
{
	m_tString.Append(str.m_tString);
}

template<typename CharT> GINLINE
gvoid GBaseString<CharT>::Append(GBaseString<CharT> &&str)
{
	m_tString.Append(GMove(str.m_tString));
}

template<typename CharT> GINLINE
gbool GBaseString<CharT>::Equals(const GBaseString<CharT> &str, gbool isSensitive) const
{
	// TODO
	return false;
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::Trim() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT>();
	}

	typename GBaseString<CharT>::StringDataT str(size);
	str.Reserve(size);
	GCString::Trim(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return GBaseString<CharT>(str);
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::TrimLeft() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT>();
	}

	GBaseString<CharT> str(size);
	str.Reserve(size);
	GCString::TrimLeft(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return str;
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::TrimRight() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT>();
	}

	GBaseString<CharT> str(size);
	str.Reserve(size);
	GCString::TrimRight(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return str;
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::ToUpper() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT>();
	}

	GBaseString<CharT> str(*this);
	GCString::MakeUpper(str.m_tString.Start(), size);
	return str;
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::ToLower() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT>();
	}

	GBaseString<CharT> str(*this);
	GCString::MakeLower(str.m_tString.Start(), size);
	return str;
}

template<typename CharT> GINLINE
GBaseString<CharT> &GBaseString<CharT>::Replace(const GBaseString<CharT> &from, const GBaseString<CharT> &to, gbool isSensitive)
{
	// TODO
	return GBaseString<CharT>(*this);
}

template<typename CharT> GINLINE
GStringListT<GBaseString<CharT>> GBaseString<CharT>::Split(const GBaseString<CharT> &sep, gbool ignoreEmpty, gbool isSensitive) const
{
	// TODO
	return GStringListT<GBaseString<CharT>>();
}

template<typename CharT> GINLINE
gsize GBaseString<CharT>::Find(CharT c, gsize start, gbool isSensitive) const
{
	// TODO
	return 0;
}

template<typename CharT> GINLINE
gsize GBaseString<CharT>::Find(const GBaseString<CharT> &str, gsize start, gbool isSensitive) const
{
	// TODO
	return 0;
}

template<typename CharT> GINLINE
GBaseString<CharT> GBaseString<CharT>::SubString(gsize start, gsize length) const
{
	// TODO
	return GBaseString<CharT>();
}

template<> GINLINE
gcstring8 GBaseString<gchar8>::CString() const
{
	if (IsEmpty())
	{
		return GUTF8("");
	}
	return m_tString.Start();
}

template<> GINLINE
gcstring16 GBaseString<gchar16>::CString() const
{
	if (IsEmpty())
	{
		return GUTF16("");
	}
	return m_tString.Start();
}

template<> GINLINE
gcstring32 GBaseString<gchar32>::CString() const
{
	if (IsEmpty())
	{
		return GUTF32("");
	}
	return m_tString.Start();
}

}

#endif // _CORE_BASE_STRING_INLINE_
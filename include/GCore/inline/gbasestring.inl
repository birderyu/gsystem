#ifndef _CORE_BASE_STRING_INLINE_
#define _CORE_BASE_STRING_INLINE_

#include "gcstring.h"

namespace gsystem {

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString()
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(CharT c)
	: m_tString(1)
{
	m_tString.Resize(1);
	m_tString[0] = c;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(typename GBaseString<CharT, LOCAL_SIZE>::CStringT str)
{
	gsize size = GCString::Size(str);
	m_tString.Resize(size);
	GCString::Copy(str, size, m_tString.Start());
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(typename GBaseString<CharT, LOCAL_SIZE>::CStringT str, gsize size)
	: m_tString(str, size)
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(const typename GBaseString<CharT, LOCAL_SIZE>::StringDataT &str)
	: m_tString(str)
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(typename GBaseString<CharT, LOCAL_SIZE>::StringDataT &&str)
	: m_tString(GForward<typename GBaseString<CharT, LOCAL_SIZE>::StringDataT>(str))
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(const GBaseString<CharT, LOCAL_SIZE> &str)
	: m_tString(str.m_tString)
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE>::GBaseString(GBaseString<CharT, LOCAL_SIZE> &&str)
	: m_tString(GMove(str.m_tString))
{

}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
typename GBaseString<CharT, LOCAL_SIZE>::CStringT GBaseString<CharT, LOCAL_SIZE>::CString() const
{
	return m_tString.Start();
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gsize GBaseString<CharT, LOCAL_SIZE>::Size() const
{
	return m_tString.Size();
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gbool GBaseString<CharT, LOCAL_SIZE>::IsEmpty() const
{
	return m_tString.IsEmpty();
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
CharT &GBaseString<CharT, LOCAL_SIZE>::GetAt(gsize pos)
{
	return m_tString.GetAt(pos);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
const CharT &GBaseString<CharT, LOCAL_SIZE>::GetAt(gsize pos) const
{
	return m_tString.GetAt(pos);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
CharT *GBaseString<CharT, LOCAL_SIZE>::CursorAt(gsize)
{
	return m_tString.CursorAt(pos);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
const CharT *GBaseString<CharT, LOCAL_SIZE>::CursorAt(gsize) const
{
	return m_tString.CursorAt(pos);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gvoid GBaseString<CharT, LOCAL_SIZE>::Resize(gsize size)
{
	m_tString.Resize(size);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gvoid GBaseString<CharT, LOCAL_SIZE>::Reserve(gsize size)
{
	m_tString.Reserve(capacity);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gbool GBaseString<CharT, LOCAL_SIZE>::StartWith(CharT c) const
{
	if (IsEmpty())
	{
		return false;
	}
	return GetAt[0] == c;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gbool GBaseString<CharT, LOCAL_SIZE>::EndWith(CharT c) const
{
	if (IsEmpty())
	{
		return false;
	}
	return GetAt(Size() - 1) == c;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gvoid GBaseString<CharT, LOCAL_SIZE>::Append(const GBaseString<CharT, LOCAL_SIZE> &str)
{
	m_tString.Append(str.m_tString);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gvoid GBaseString<CharT, LOCAL_SIZE>::Append(GBaseString<CharT, LOCAL_SIZE> &&str)
{
	m_tString.Append(GMove(str.m_tString));
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gbool GBaseString<CharT, LOCAL_SIZE>::Equals(const GBaseString<CharT, LOCAL_SIZE> &str, gbool isSensitive) const
{
	// TODO
	return false;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::Trim() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT, LOCAL_SIZE>();
	}

	typename GBaseString<CharT, LOCAL_SIZE>::StringDataT str(size);
	str.Reserve(size);
	GCString::Trim(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return GBaseString<CharT, LOCAL_SIZE>(str);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::TrimLeft() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT, LOCAL_SIZE>();
	}

	GBaseString<CharT, LOCAL_SIZE> str(size);
	str.Reserve(size);
	GCString::TrimLeft(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return str;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::TrimRight() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT, LOCAL_SIZE>();
	}

	GBaseString<CharT, LOCAL_SIZE> str(size);
	str.Reserve(size);
	GCString::TrimRight(m_tString.Start(), size, str.Start(), size);
	str.Resize(size);
	return str;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::ToUpper() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT, LOCAL_SIZE>();
	}

	GBaseString<CharT, LOCAL_SIZE> str(*this);
	GCString::MakeUpper(str.m_tString.Start(), size);
	return str;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::ToLower() const
{
	gsize size = Size();
	if (0 == size)
	{
		return GBaseString<CharT, LOCAL_SIZE>();
	}

	GBaseString<CharT, LOCAL_SIZE> str(*this);
	GCString::MakeLower(str.m_tString.Start(), size);
	return str;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> &GBaseString<CharT, LOCAL_SIZE>::Replace(const GBaseString<CharT, LOCAL_SIZE> &from, const GBaseString<CharT, LOCAL_SIZE> &to, gbool isSensitive)
{
	// TODO
	return GBaseString<CharT, LOCAL_SIZE>(*this);
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GStringListT<GBaseString<CharT, LOCAL_SIZE>> GBaseString<CharT, LOCAL_SIZE>::Split(const GBaseString<CharT, LOCAL_SIZE> &sep, gbool ignoreEmpty, gbool isSensitive) const
{
	// TODO
	return GStringListT<GBaseString<CharT, LOCAL_SIZE>>();
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gsize GBaseString<CharT, LOCAL_SIZE>::Find(CharT c, gsize start, gbool isSensitive) const
{
	// TODO
	return 0;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
gsize GBaseString<CharT, LOCAL_SIZE>::Find(const GBaseString<CharT, LOCAL_SIZE> &str, gsize start, gbool isSensitive) const
{
	// TODO
	return 0;
}

template<typename CharT, gsize LOCAL_SIZE> GINLINE
GBaseString<CharT, LOCAL_SIZE> GBaseString<CharT, LOCAL_SIZE>::SubString(gsize start, gsize length) const
{
	// TODO
	return GBaseString<CharT, LOCAL_SIZE>();
}

}

#endif // _CORE_BASE_STRING_INLINE_
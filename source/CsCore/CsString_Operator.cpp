#include "CsString.h"

cs_bool CsString::operator == (const CsString &sStr) const
{
	// TODO
	return false;
}

CsString &CsString::operator+=(const CsString &sStr)
{
	// TODO
	return *this;
}

CsString &CsString::operator=(const CsString &sStr)
{
	// TODO
	return *this;
}

cs_char CsString::operator[](cs_size_t pos) const
{
	return GetAt(pos);
}

cs_char &CsString::operator[](cs_size_t pos)
{
	return GetAt(pos);
}

CsString operator+(const CsString &s1, const CsString &s2)
{
	CsString sStr(s1);
	sStr += s2;
	return sStr;
}
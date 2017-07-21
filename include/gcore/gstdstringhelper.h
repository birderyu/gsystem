#ifndef _CORE_STD_STRING_UTILITY_H_
#define _CORE_STD_STRING_UTILITY_H_

#include "gtype.h"

#ifdef G_NEED_ALL_FUNCTION

#include <string>
#include <sstream>
#include <vector>

namespace gsystem { // gsystem

class GAPI GStdStringHelper
{
public:
	static std::string Trim(const std::string &sStr);
	static std::string ToUpper(const std::string &sStr);
	static std::string ToLower(const std::string &sStr);
	static std::string Replace(const std::string &sStr, const std::string &from,
		const std::string &to, gbool bIsSensitive);
	static std::vector<std::string> Split(const std::string &sStr, const std::string &sSep,
		gbool bIgnoreEmpty, gbool bIsSensitive);
	static gint Find(const std::string &str, gchar c, gsize start, gbool bIsSensitive);
	static gint Find(const std::string &str, const std::string &tar, gsize start, gbool bIsSensitive);

	template <typename T>
	static std::string FromNum(T nNum, gint nBase = 10);

	template <typename T>
	static T ToNum(const std::string &str, gbool *bIsOk = GNULL);
};

template <typename T>
std::string GStdStringHelper::FromNum(T nNum, gint nBase)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << nNum;
	return oss.str();
}

template <typename T>
T GStdStringHelper::ToNum(const std::string &str,gbool *bIsOk)
{
	std::istringstream iss(str.c_str());
	T nNum;
	if (bIsOk)
	{
		*bIsOk = false;
	}
	if (iss >> nNum)
	{
		if (bIsOk)
		{
			*bIsOk = true;
		}
	}
	return nNum;
}

} // namespace gsystem

#endif // G_NEED_ALL_FUNCTION

#endif // _CORE_STD_STRING_UTILITY_H_
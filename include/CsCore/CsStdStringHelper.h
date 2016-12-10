#ifndef _CORE_STD_STRING_UTILITY_H_
#define _CORE_STD_STRING_UTILITY_H_

#include "CsGlobal.h"
#include <string>
#include <sstream>
#include <vector>

class CS_API CsStdStringHelper
{
public:
	static std::string Trim(const std::string &sStr);
	static std::string ToUpper(const std::string &sStr);
	static std::string ToLower(const std::string &sStr);
	static std::string Replace(const std::string &sStr, const std::string &from,
		const std::string &to, cs_bool bIsSensitive);
	static cs_void Split(const std::string &sStr, const std::string &sSep,
		cs_bool bIgnoreEmpty, cs_bool bIsSensitive,
		std::vector<std::string> &tStrs);
	static cs_int Find(const std::string &str, cs_char c, cs_size_t start, cs_bool bIsSensitive);
	static cs_int Find(const std::string &str, const std::string &tar, cs_size_t start, cs_bool bIsSensitive);

	template <typename T>
	static std::string FromNum(T nNum, cs_int nBase = 10);

	template <typename T>
	static T ToNum(const std::string &str, cs_bool *bIsOk = NULL);
};

template <typename T>
std::string CsStdStringHelper::FromNum(T nNum, cs_int nBase)
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
T CsStdStringHelper::ToNum(const std::string &str,cs_bool *bIsOk)
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

#endif // _CORE_STD_STRING_UTILITY_H_